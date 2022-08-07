package src

import (
	"fmt"
	"net"
	"os"
	"strconv"
	"time"
)

func initConnections(myID int) map[int]*net.UDPConn {
	connections := make(map[int]*net.UDPConn)
	for idx, port := range os.Args[2:len(os.Args)] {
		if idx+1 == myID {
			continue
		}
		conn, err := udpConnect(port)
		CheckError(err)
		connections[idx+1] = conn
	}
	return connections
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
	connections := initConnections(myID)
	defer closeConnections(connections)

	ch := make(chan string)
	go readInput(ch)

	logicalClock := NewScalarClock()
	go serve(ports[myID-1])
	for {
		select {
		case command := <-ch:
			id, err := strconv.Atoi(command)
			if err != nil {
				fmt.Println("invalid command, ignoring...")
				break
			}
			if id < 1 || id > len(ports) {
				fmt.Println("given id does not exist in context, ignoring...")
				break
			}
			if id == myID {
				logicalClock.InternalEvent()
			} else {
				logicalClock.SendMessage(connections[id])
			}
		default:
		}
		time.Sleep(time.Second * 1)
	}
}
