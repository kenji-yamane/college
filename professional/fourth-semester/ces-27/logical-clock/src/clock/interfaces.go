package clock

type LogicalClock interface {
	InternalEvent()
	ExternalEvent(processID int, externalClock string)
	GetClockStr() string
}
