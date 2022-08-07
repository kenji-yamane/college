package clock

import (
	"fmt"
	"github.com/kenji-yamane/College/professional/fourth-semester/ces-27/logical-clock/src/math"
	"strconv"
)

type ScalarClock struct {
	ticks int
}

func NewScalarClock() LogicalClock {
	return &ScalarClock{
		ticks: 0,
	}
}

func (c *ScalarClock) InternalEvent() {
	c.ticks++
	c.echoClock()
}

func (c *ScalarClock) ExternalEvent(processID int, externalClock string) {
	externalTicks, err := strconv.Atoi(externalClock)
	if err != nil {
		fmt.Println("invalid clock string, ignoring...")
		return
	}
	c.ticks = math.Max(externalTicks, c.ticks) + 1
	c.echoClock()
}

func (c *ScalarClock) GetClockStr() string {
	return strconv.Itoa(c.ticks)
}

func (c *ScalarClock) echoClock() {
	fmt.Println("logical clock: ", c.ticks)
}
