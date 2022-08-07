package src

import (
	"fmt"
	"net"
	"strconv"
)

type ScalarClock struct {
	ticks int
}

func NewScalarClock() *ScalarClock {
	return &ScalarClock{
		ticks: 0,
	}
}

func (c *ScalarClock) InternalEvent() {
	c.ticks++
	c.echoClock()
}

func (c *ScalarClock) ExternalEvent(externalTicks int) {
	c.ticks = Max(externalTicks, c.ticks) + 1
	c.echoClock()
}

func (c *ScalarClock) SendMessage(conn *net.UDPConn) {
	udpSend(conn, strconv.Itoa(c.ticks))
}

func (c *ScalarClock) echoClock() {
	fmt.Println("logical clock: ", c.ticks)
}
