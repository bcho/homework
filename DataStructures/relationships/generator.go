package main

/*
This application is used for generating random data for `relationship` program.

Usage Examples:

    ./generator
    ./generator -name 25 -relationship 90 -query 60


Default Parameters:

    name: 10
    relationship: 80
    query: 120


Output Format:

3       # NAME COUNT
a
b
c
2       # RELATIONSHIP COUNT
a b
c b
2       # QUERY COUNT
a b
c b
*/

import (
	"flag"
	"fmt"
	"math/rand"
	"strings"
	"time"
)

const (
	NAME_COUNT         = 10
	RELATIONSHIP_COUNT = 80
	QUERY_COUNT        = 120

	NAME_MINIMUM_LENGTH   = 5
	NAME_MAXIMUM_LENGTH   = 50
	CHARACTER_SETS        = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMOPQRSTUVWXYZ0123456789"
	CHARACTER_SETS_LENGTH = len(CHARACTER_SETS)
)

type Options struct {
	Name, Relationship, Query int
}

// Parse generate options from command line.
func (o *Options) ParseFromFlags() {
	flag.IntVar(&o.Name, "name", NAME_COUNT, "Unique names to be generated.")
	flag.IntVar(&o.Relationship, "relationship", RELATIONSHIP_COUNT,
		"Relationships pairs count.")
	flag.IntVar(&o.Query, "query", QUERY_COUNT, "Query count.")

	flag.Parse()
}

type Person struct {
	Name string
}

// Generate a person with given name.
func NewPerson(name string) *Person {
	return &Person{name}
}

// Generate a person with random name.
func NewRandomPerson() (p *Person) {
	name_length := RandomIntFromRange(NAME_MINIMUM_LENGTH, NAME_MAXIMUM_LENGTH)
	name := RandomString(name_length)

	return NewPerson(name)
}

// Print person structure.
func (p Person) Print() {
	fmt.Println(p.Name)
}

type PersonSet struct {
	Capacity, Used int
	// XXX array/slice
	Persons []*Person
}

// Create a person set.
func NewPersonSet(capacity int) *PersonSet {
	return &PersonSet{capacity, 0, make([]*Person, capacity, capacity)}
}

// Create a person set with random person.
func NewRandomPersonSet(capacity int) *PersonSet {
	s := NewPersonSet(capacity)

	for !s.IsFull() {
		s.Add(NewRandomPerson())
	}

	return s
}

// Check if the set contains specify person.
func (s PersonSet) Contains(p *Person) bool {
	for i := 0; i < s.Used; i++ {
		if s.Persons[i] == nil {
			continue
		}

		if name := s.Persons[i].Name; p.Name == name {
			return true
		}
	}

	return false
}

// Add a person to set.
func (s *PersonSet) Add(p *Person) error {
	if s.Contains(p) {
		return PersonSetAddError{}
	}

	s.Persons[s.Used] = p
	s.Used = s.Used + 1

	return nil
}

// Indicate if the set is full.
func (s PersonSet) IsFull() bool {
	return s.Used == s.Capacity
}

// Pick a person pair from set.
func (s PersonSet) Pair(a, b int) (*Person, *Person) {
	return s.Persons[a], s.Persons[b]
}

// Pick randomly a person pair from set.
func (s PersonSet) RandomPair() (*Person, *Person) {
	var a, b int
	a = RandomIntFromRange(0, s.Used)
	for b = a; a == b; {
		b = RandomIntFromRange(0, s.Used)
	}

	return s.Pair(a, b)
}

// Print person set structure.
func (s PersonSet) Print() {
	fmt.Println(s.Used)

	for i := 0; i < s.Used; i++ {
		s.Persons[i].Print()
	}
}

type PersonSetAddError struct{}

func (e PersonSetAddError) Error() string {
	return "Add failed."
}

// Generate a random string with given length.
func RandomString(length int) (s string) {
	picked := make([]string, length, length)

	for ; length > 0; length -= 1 {
		c := CHARACTER_SETS[RandomIntFromRange(0, CHARACTER_SETS_LENGTH)]
		picked[length-1] = string(c)
	}

	return strings.Join(picked, "")
}

// Generate a random int from a range [lo, hi).
func RandomIntFromRange(lo, hi int) int {
	return rand.Intn(hi-lo) + lo
}

func main() {
	// Seed the program.
	rand.Seed(time.Now().UnixNano())

	options := Options{}
	options.ParseFromFlags()

	s := NewRandomPersonSet(options.Name)

	// Print names
	s.Print()

	// Print relationships
	fmt.Println(options.Relationship)
	for i := 0; i < options.Relationship; i++ {
		a, b := s.RandomPair()
		fmt.Printf("%s %s\n", a.Name, b.Name)
	}

	// Print query
	fmt.Println(options.Query)
	for i := 0; i < options.Query; i++ {
		a, b := s.RandomPair()
		fmt.Printf("%s %s\n", a.Name, b.Name)
	}
}
