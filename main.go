package main

import (
	"github.com/yene/kBerry/kdrive"
)

func main() {
	kdrive.EnableLogger()
	kdrive.Connect("/dev/ttyAMA0")
	kdrive.GAWrite(0x901, true)
	kdrive.ConnectPacketTrace()
	kdrive.Close()
}
