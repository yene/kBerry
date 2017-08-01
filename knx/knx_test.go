package knx_test

import (
	"testing"

	"github.com/yene/kBerry/knx"
)

func TestGA(t *testing.T) {
	ga := knx.GAFromString("1/1/1")
	gi := knx.GAFromInt(0x901) // 0x901 is 2305
	if ga != gi {
		t.Error("Parsed by string and parsed by int should be equal.")
	}
}

func TestDPT(t *testing.T) {
	cases := []struct {
		A        string
		B        string
		Expected bool
		Name     string
	}{
		{"1.001", "1.001", true, ""},
		{"9.001", "9.001", true, ""},
		{"9.001", "1.001", false, ""},
		{"14.079", "14.079", true, ""},
		{"14.079", "1.001", false, ""},
		{"202.002", "202.002", true, ""},
		{"202.002", "1.001", false, ""},
		{".002", "1.001", false, ""},
		{"1232.002", "1.001", false, ""},
	}

	// Test packing and unpacking DPT
	for _, tc := range cases {
		t.Run(tc.Name, func(t *testing.T) {
			dpt := knx.DPTFromString(tc.A)
			res := dpt.String() == tc.B
			if res != tc.Expected {
				if tc.Expected {
					t.Fatal(dpt, "should be equal to", tc.B)
				} else {
					t.Fatal(dpt, "should not be equal to", tc.B)
				}
			}
		})
	}

}
