package main

import (
	"fmt"
	"os"
)

// CheckError prints the error on the default output and exits code
func CheckError(err error) {
	if err != nil {
		fmt.Println("Error: ", err)
		os.Exit(0)
	}
}
