package main

import (
	"fmt"

	"github.com/yene/kBerry/kdrive"
)

func main() {
	kdrive.EnableLogger()
	kdrive.OpenFT12("/dev/ttyAMA0")
	fmt.Println("current Individual Address", kdrive.GetAddress())
	kdrive.RegisterCallback()
	kdrive.AddGA(0x901, "1.001") // 2305
	kdrive.AddGA(0x90A, "2.001") // 2314
	kdrive.AddGA(2315, "3.000")
	kdrive.AddGA(2316, "4.000")
	kdrive.AddGA(2317, "5.000")
	kdrive.AddGA(2318, "6.000")
	kdrive.AddGA(2319, "7.000")
	kdrive.AddGA(2320, "8.000")
	kdrive.AddGA(2321, "9.000")
	kdrive.AddGA(2322, "10.001")
	kdrive.AddGA(2323, "10.001")
	kdrive.AddGA(2324, "10.001")
	kdrive.AddGA(2325, "11.001")
	kdrive.AddGA(2326, "11.001")
	kdrive.AddGA(2327, "11.001")
	kdrive.AddGA(2328, "12.001")
	kdrive.AddGA(2329, "13.001")
	kdrive.AddGA(2330, "14.001")
	kdrive.AddGA(2331, "15.001")
	kdrive.AddGA(2332, "16.001")
	kdrive.TestCallback()
	kdrive.Close()
}
