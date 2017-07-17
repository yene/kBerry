package main

import (
	"github.com/yene/kBerry/kdrive"
)

func main() {
	kdrive.EnableLogger()
	kdrive.ScanAndOpen()
	//kdrive.OpenFT12("/dev/ttyAMA0")
	//kdrive.OpenIP("192.168.1.222")
	kdrive.GAWrite(0x901, true)
	kdrive.ConnectPacketTrace()
	kdrive.Close()
}
