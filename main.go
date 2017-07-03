package main

import (
	"github.com/yene/kBerry/kDrive"
)

func main() {
	kDrive.EnableLogger()
	kDrive.Connect("/dev/ttyAMA0")
	kDrive.GAWrite(0x901, true)
	kDrive.ConnectPacketTrace()
	kDrive.Close()
}
