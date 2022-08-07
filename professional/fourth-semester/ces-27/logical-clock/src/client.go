package src

import (
	"fmt"
	"net"
)

func udpConnect(port string) (*net.UDPConn, *net.UDPAddr) {
	serverAddr, err := net.ResolveUDPAddr("udp", "127.0.0.1:"+port)
	CheckError(err)

	localAddr, err := net.ResolveUDPAddr("udp", "127.0.0.1:0")
	CheckError(err)

	conn, err := net.DialUDP("udp", localAddr, serverAddr)
	CheckError(err)

	return conn, serverAddr
}

func udpSend(conn *net.UDPConn, msg string) {
	_, err := conn.Write([]byte(msg))
	if err != nil {
		fmt.Println(msg, err)
	} else {
		fmt.Println("sending message: ", msg)
	}
}
