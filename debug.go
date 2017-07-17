package main

import (
	"fmt"
	"net"
	"os/exec"
	"strings"
)

func printIP() {
	ifaces, _ := net.Interfaces()
	// handle _
	for _, i := range ifaces {
		fmt.Println(i.Name, i.Index)
		addrs, _ := i.Addrs()
		// handle _
		for _, addr := range addrs {
			var ip net.IP
			switch v := addr.(type) {
			case *net.IPNet:
				ip = v.IP
			case *net.IPAddr:
				ip = v.IP
			}
			fmt.Println(ip)
		}
	}
}

func ping() {
	out, _ := exec.Command("ping", "192.168.1.222", "-c 5", "-i 3", "-w 10").Output()
	if strings.Contains(string(out), "Destination Host Unreachable") {
		fmt.Println("TANGO DOWN")
	} else {
		fmt.Println("IT'S ALIVEEE")
	}
}
