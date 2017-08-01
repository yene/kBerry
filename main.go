package main

import (
	"github.com/yene/kBerry/kdrive"
)

func main() {
	kdrive.EnableLogger()
	kdrive.OpenFT12("/dev/ttyAMA0")
	kdrive.GAWrite(0x901, true)
	kdrive.ConnectPacketTrace()
	kdrive.Close()
}
