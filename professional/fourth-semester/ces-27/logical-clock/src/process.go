package src

import (
	"fmt"
	"github.com/kenji-yamane/College/professional/fourth-semester/ces-27/logical-clock/src/clock"
	"net"
	"os"
	"strconv"
	"time"
)

func initConnections(myID int) (map[int]*net.UDPConn, map[string]int) {
	connections := make(map[int]*net.UDPConn)
	portResolve := make(map[string]int)
	for idx, port := range os.Args[2:len(os.Args)] {
		if idx+1 == myID {
			continue
		}
		conn, serverAddr := udpConnect(port)
		connections[idx+1] = conn
		portResolve[strconv.Itoa(serverAddr.Port)] = idx + 1
	}
	return connections, portResolve
}

func closeConnections(connections map[int]*net.UDPConn) {
	for _, conn := range connections {
		err := conn.Close()
		CheckError(err)
	}
}

// Execute parses arguments into process information and
// executes accordingly
func Execute() {
	if len(os.Args) < 4 {
		CheckError(fmt.Errorf("not enough ports given as arguments"))
	}
	myID, err := strconv.Atoi(os.Args[1])
	if err != nil {
		CheckError(fmt.Errorf("first argument should be a number representing the sequential process ID"))
	}
	ports := os.Args[2:len(os.Args)]

	connections, portResolve := initConnections(myID)
	defer closeConnections(connections)

	terminalCh := make(chan string)
	go readInput(terminalCh)

	serverCh := make(chan IncomingMessage)
	go serve(serverCh, ports[myID-1])

	var logicalClock clock.LogicalClock
	logicalClock = clock.NewScalarClock()
	for {
		select {
		case command, valid := <-terminalCh:
			if !valid {
				break
			}
			id, err := strconv.Atoi(command)
			if err != nil {
				fmt.Println("invalid command, ignoring...")
				break
			}
			if id < 1 || id > len(ports) {
				fmt.Println("given id does not exist in context, ignoring...")
				break
			}
			logicalClock.InternalEvent()
			if id != myID {
				udpSend(connections[id], logicalClock.GetClockStr())
			}
		case incomingMsg, valid := <-serverCh:
			if !valid {
				break
			}
			incomingID, ok := portResolve[strconv.Itoa(incomingMsg.Sender.Port)]
			if !ok {
				//fmt.Println("unknown sender, ignoring...")
				//break
			}
			logicalClock.ExternalEvent(incomingID, incomingMsg.Msg)
		default:
		}
		time.Sleep(time.Second * 1)
	}
}
