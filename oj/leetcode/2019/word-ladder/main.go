package main

import "fmt"

func ladderLength(beginWord string, endWord string, wordList []string) int {
	if len(wordList) < 1 {
		return 0
	}

	dict := map[string]struct{}{}
	for _, word := range wordList {
		dict[word] = struct{}{}
	}
	if _, ok := dict[endWord]; !ok {
		// special case
		return 0
	}

	pathLength := 1
	// each pass process one *whole* level
	shortPending := map[string]struct{}{}
	shortPending[beginWord] = struct{}{}
	longPending := map[string]struct{}{}
	longPending[endWord] = struct{}{}
	visitedWords := map[string]struct{}{}
	for len(shortPending) > 0 && len(longPending) > 0 {
		// O(n^d) >> O(n^(d/2) + n^(d/2))
		// so it's better to search both end (level search)
		if len(shortPending) > len(longPending) {
			// each pass, start from the shorter end
			longPending, shortPending = shortPending, longPending
		}

		// generate new level
		newPendingWords := map[string]struct{}{}
		// process this level
		for word, _ := range shortPending {
			visitedWords[word] = struct{}{}
			for i := 0; i < len(word); i++ {
				for c := 'a'; c <= 'z'; c++ {
					newWord := word[:i] + string(c) + word[i+1:]
					if _, valid := dict[newWord]; !valid {
						continue
					}
					if newWord == word {
						continue
					}
					if _, overlapped := longPending[newWord]; overlapped {
						// two ends meet, return
						return pathLength + 1
					}
					if _, visited := visitedWords[newWord]; visited {
						continue
					}
					newPendingWords[newWord] = struct{}{}
				}
			}
		}
		shortPending = newPendingWords
		pathLength += 1
	}

	return 0
}

func main() {
	if d := ladderLength("a", "c", []string{"a", "b", "c"}); d != 2 {
		panic(fmt.Sprintf("expected 2, got: %d", d))
	}
	fmt.Println("====")
	if d := ladderLength("a", "c", []string{"b", "c"}); d != 2 {
		panic(fmt.Sprintf("expected 3, got: %d", d))
	}
	if d := ladderLength("hot", "dog", []string{"hot", "dog"}); d != 0 {
		panic(fmt.Sprintf("expected 1, got: %d", d))
	}
}
