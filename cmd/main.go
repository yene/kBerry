package main

import (
	"fmt"
	"log"
	"time"

	"github.com/yene/kBerry/kdrive"
	"github.com/yene/kBerry/knx"
)

func main() {
	kdrive.EnableLogger()
	err := kdrive.OpenFT12("/dev/ttyAMA0")
	if err != nil {
		log.Fatal(err)
	}
	fmt.Println("current Individual Address", kdrive.GetAddress())
	//kdrive.GetSerialnumber(kdrive.GetAddress())
	serial, err := kdrive.GetSerialnumber(knx.IAFromString("1.1.4"))
	if err != nil {
		fmt.Println("Coud not get serial number:", err)
	} else {
		fmt.Println("Serial number of 1.1.4 is", serial)
	}

	kdrive.RegisterCallback()
	kdrive.AddGroupaddress(knx.GAFromInt(0x901), knx.DPTFromString("1.001"))
	kdrive.AddGroupaddress(knx.GAFromInt(0x90A), knx.DPTFromString("2.001"))
	kdrive.AddGroupaddress(knx.GAFromInt(2315), knx.DPTFromString("3.000"))
	kdrive.AddGroupaddress(knx.GAFromInt(2316), knx.DPTFromString("4.000"))
	kdrive.AddGroupaddress(knx.GAFromInt(2317), knx.DPTFromString("5.000"))
	kdrive.AddGroupaddress(knx.GAFromInt(2318), knx.DPTFromString("6.000"))
	kdrive.AddGroupaddress(knx.GAFromInt(2319), knx.DPTFromString("7.000"))
	kdrive.AddGroupaddress(knx.GAFromInt(2320), knx.DPTFromString("8.000"))
	kdrive.AddGroupaddress(knx.GAFromInt(2321), knx.DPTFromString("9.000"))
	kdrive.AddGroupaddress(knx.GAFromInt(2322), knx.DPTFromString("10.001"))
	kdrive.AddGroupaddress(knx.GAFromInt(2325), knx.DPTFromString("11.001"))
	kdrive.AddGroupaddress(knx.GAFromInt(2328), knx.DPTFromString("12.001"))
	kdrive.AddGroupaddress(knx.GAFromInt(2329), knx.DPTFromString("13.001"))
	kdrive.AddGroupaddress(knx.GAFromInt(2330), knx.DPTFromString("14.001"))
	kdrive.AddGroupaddress(knx.GAFromInt(2331), knx.DPTFromString("15.001"))
	kdrive.AddGroupaddress(knx.GAFromInt(2332), knx.DPTFromString("16.001"))

	kdrive.GAWrite(knx.GAFromInt(0x901), 1)
	kdrive.GAWrite(knx.GAFromInt(0x90A), 1, 1)
	kdrive.GAWrite(knx.GAFromInt(2315), 1, 0x05)
	kdrive.GAWrite(knx.GAFromInt(2316), "A")
	kdrive.GAWrite(knx.GAFromInt(2317), 33)
	kdrive.GAWrite(knx.GAFromInt(2318), -5)
	kdrive.GAWrite(knx.GAFromInt(2319), 0xAFFE)
	kdrive.GAWrite(knx.GAFromInt(2320), -1024)
	kdrive.GAWrite(knx.GAFromInt(2321), 12.25)
	kdrive.GAWrite(knx.GAFromInt(2322), "") // Time
	kdrive.GAWrite(knx.GAFromInt(2325), "") // Date
	kdrive.GAWrite(knx.GAFromInt(2328), uint(0xDEADBEEF))
	kdrive.GAWrite(knx.GAFromInt(2329), -30000)
	kdrive.GAWrite(knx.GAFromInt(2330), 2025.12345)
	kdrive.GAWrite(knx.GAFromInt(2331), 1) // Entrance access
	kdrive.GAWrite(knx.GAFromInt(2332), "Weinzierl Eng!")

	time.Sleep(time.Second * 1)
	kdrive.Close()

}
