package src

import (
	"fmt"
	"net"
)

func serve(port string) {
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
		fmt.Println("Received ", string(buf[0:n]), " from ", addr)
		if err != nil {
			fmt.Println("Error: ", err)
		}
	}
}
