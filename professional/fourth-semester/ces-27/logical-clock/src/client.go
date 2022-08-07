package src

import (
	"fmt"
	"net"
)

func udpConnect(port string) (*net.UDPConn, error) {
	ServerAddr, err := net.ResolveUDPAddr("udp", "127.0.0.1:"+port)
	CheckError(err)

	LocalAddr, err := net.ResolveUDPAddr("udp", "127.0.0.1:0")
	CheckError(err)

	return net.DialUDP("udp", LocalAddr, ServerAddr)
}

func udpSend(conn *net.UDPConn, msg string) {
	_, err := conn.Write([]byte(msg))
	if err != nil {
		fmt.Println(msg, err)
	}
}
