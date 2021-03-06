// Package knx provides functions and types for working with KNX.
package knx

import (
	"fmt"
	"log"
)

type IndividualAddress struct {
	Area   int // 4 bits
	Line   int // 4 bits
	Device int // 8 bits
}

func (ia IndividualAddress) String() string {
	return fmt.Sprintf("%d.%d.%d", ia.Area, ia.Line, ia.Device)
}

func (ia IndividualAddress) Int() int {
	return ia.Area<<12 + ia.Line<<8 + ia.Device
}

func IAFromString(s string) IndividualAddress {
	ia := IndividualAddress{}
	if _, err := fmt.Sscanf(s, "%d.%d.%d", &ia.Area, &ia.Line, &ia.Device); err == nil {
		return ia
	}
	log.Printf("Error parsing Individual Address: %s", s)

	return ia
}

func IAFromInt(i int) IndividualAddress {
	ia := IndividualAddress{}
	// 00000000 00001111 = 0x0F 4 bits
	// 00000000 11111111 = 0xFF 8 bits
	ia.Area = i >> 12 & 0x0F
	ia.Line = i >> 8 & 0x0F
	ia.Device = i & 0xFF
	return ia
}

// GroupAddress
type GroupAddress struct {
	Main   int // 5 bits
	Middle int // 3 bits
	Sub    int // 8 bits
}

func (g GroupAddress) String() string {
	return fmt.Sprintf("%d/%d/%d", g.Main, g.Middle, g.Sub)
}

// GAFromString converts a string to GroupAddress.
func GAFromString(s string) GroupAddress {
	ga := GroupAddress{Main: 0, Middle: 0, Sub: 0}
	if _, err := fmt.Sscanf(s, "%d/%d/%d", &ga.Main, &ga.Middle, &ga.Sub); err == nil {
		return ga
	}
	log.Printf("Error parsing GA: %s", s)
	return ga
}

func (g GroupAddress) Int() int {
	return g.Main<<11 + g.Middle<<8 + g.Sub
}

func GAFromInt(i int) GroupAddress {
	ga := GroupAddress{Main: 0, Middle: 0, Sub: 0}
	// Three Style Address 5/3/8
	// 00000000 00011111 = 0x1F 5 bits
	// 00000000 00000111 = 0x07 3 bits
	// 00000000 11111111 = 0xFF 8 bits
	ga.Main = i >> 11 & 0x1F
	ga.Middle = i >> 8 & 0x07
	ga.Sub = i & 0xFF
	return ga
}

// DPT represents a KNX datapoint. Main is the format encoding, Sub is the range and unit.
type DPT struct {
	Main uint16
	Sub  uint16
}

func (d DPT) String() string {
	return fmt.Sprintf("%d.%03d", d.Main, d.Sub)
}

// DPTFromString converts a string to DPT.
func DPTFromString(s string) DPT {
	d := DPT{Main: 0, Sub: 0}
	if _, err := fmt.Sscanf(s, "%d.%03d", &d.Main, &d.Sub); err == nil {
		return d
	}
	log.Printf("Error parsing DPT: %s", s)
	return d
}
