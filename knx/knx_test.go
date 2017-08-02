package knx_test

import (
	"testing"

	"github.com/yene/kBerry/knx"
)

func TestIndividualAddress(t *testing.T) {
	ia := knx.IAFromString("13.13.120")
	if ia.String() != "13.13.120" {
		t.Error("Parsed IndividualAddress by string and parsed should be equal.")
	}
	if ia.Int() != 56696 {
		t.Error("Int of IndividualAddress is wrong. It is", ia.Int())
	}

	ii := knx.IAFromInt(56696)
	if ii.String() != "13.13.120" {
		t.Error("Parsed IndividualAddress by INT is wrong. It is", ii)
	}

}

func TestGA(t *testing.T) {
	ga := knx.GAFromString("1/1/1")
	gi := knx.GAFromInt(0x901) // 0x901 is 2305
	if ga != gi {
		t.Error("Parsed by string and parsed by int should be equal.")
	}
	if ga.Int() != 2305 {
		t.Error("Int of GroupAddress is wrong. It is", ga.Int())
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
