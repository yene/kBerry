package kdrive

import "github.com/yene/kBerry/knx"

var addresses map[knx.GroupAddress]knx.DPT

func init() {
	addresses = make(map[knx.GroupAddress]knx.DPT)
}

func AddGA(a int, dpt string) {
	ga := knx.GAFromInt(a)
	addresses[ga] = knx.DPTFromString(dpt)
}
