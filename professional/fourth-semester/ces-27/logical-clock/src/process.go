package src

import (
	"fmt"
	"net"
	"os"
	"strconv"
	"time"
)

func initConnections() []*net.UDPConn {
	connections := make([]*net.UDPConn, 0)
	go serve(os.Args[1])
	for _, port := range os.Args[2:len(os.Args)] {
		conn, err := udpConnect(port)
		CheckError(err)
		connections = append(connections, conn)
	}
	return connections
}

func closeConnections(connections []*net.UDPConn) {
	for _, conn := range connections {
		err := conn.Close()
		CheckError(err)
	}
}

func Execute() {
	if len(os.Args) < 3 {
		CheckError(fmt.Errorf("not enough ports given as arguments"))
	}

	connections := initConnections()
	defer closeConnections(connections)

	go serve(os.Args[1])
	i := 0
	for {
		for _, conn := range connections {
			go udpSend(conn, strconv.Itoa(i))
		}
		time.Sleep(time.Second * 1)
		i++
	}
}
