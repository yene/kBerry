package kdrive

import "github.com/yene/kBerry/knx"

var addresses map[knx.GroupAddress]knx.DPT

func init() {
	addresses = make(map[knx.GroupAddress]knx.DPT)
}

func AddGroupaddress(ga knx.GroupAddress, dpt knx.DPT) {
	addresses[ga] = dpt
}
