package main

import "fmt"

func letterCombinations(digits string) []string {
	if len(digits) < 1 {
		return nil
	}

	letters := map[string]string{
		"2": "abc",
		"3": "def",
		"4": "ghi",
		"5": "jkl",
		"6": "mno",
		"7": "pqrs",
		"8": "tuv",
		"9": "wxyz",
	}

	var rv []string
	for _, s := range letters[string(digits[0])] {
		rv = append(rv, string(s))
	}

	for _, d := range digits[1:] {
		var new []string
		for _, s := range letters[string(d)] {
			for _, r := range rv {
				new = append(new, r+string(s))
			}
		}

		rv = new
	}

	return rv
}

func main() {
	fmt.Println(letterCombinations("23"))
	fmt.Println(letterCombinations("233"), len(letterCombinations("233")))
}
