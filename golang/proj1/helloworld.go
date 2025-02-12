package main

import "fmt"

func main() {
    day := "Monday"

    switch day {
    case "Monday":
        fmt.Println("Start of the week")
    case "Friday":
        fmt.Println("Weekend is near!")
    case "Sunday":
        fmt.Println("It's a holiday!")
    default:
        fmt.Println("A regular day")
    }
}