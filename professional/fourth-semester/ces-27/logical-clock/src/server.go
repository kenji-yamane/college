package src

import (
	"fmt"
	"net"
)

func serve(ch chan string, port string) {
	/* Lets prepare a address at any address at port :port*/
	ServerAddr, err := net.ResolveUDPAddr("udp", ":"+port)
	CheckError(err)

	/* Now listen at selected port */
	ServerConn, err := net.ListenUDP("udp", ServerAddr)
	CheckError(err)
	defer func() {
		connErr := ServerConn.Close()
		CheckError(connErr)
	}()

	buf := make([]byte, 1024)
	for {
		n, addr, err := ServerConn.ReadFromUDP(buf)
		if err != nil {
			fmt.Println("Error on server: ", err)
			continue
		}
		msg := string(buf[0:n])
		fmt.Println("received ", msg, " from ", addr)
		ch <- msg
	}
}
