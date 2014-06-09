package main

import (
	"fmt"
	"strconv"
)

type Parser interface {
	Expr() error
	Term() error
	Match(string) error
}

type ParseError struct{}

func (e ParseError) Error() string {
	return "Parse error."
}

type PostfixParser struct {
	Lookahead string
}

func (p *PostfixParser) Expr() error {
	if err := p.Term(); err != nil {
		return err
	}

	for {
		if p.Lookahead == "+" {
			if err := p.Match("+"); err != nil {
				return err
			}

			if err := p.Term(); err != nil {
				return err
			}

			fmt.Print("+ ")
		} else if p.Lookahead == "-" {
			if err := p.Match("-"); err != nil {
				return err
			}

			if err := p.Term(); err != nil {
				return err
			}

			fmt.Print("- ")
		} else {
			return nil
		}
	}
}

func (p *PostfixParser) Term() error {
	if _, err := strconv.Atoi(p.Lookahead); err != nil {
		return err
	}

	fmt.Printf("%s ", p.Lookahead)
	p.Match(p.Lookahead)

	return nil
}

func (p *PostfixParser) Match(t string) error {
	if p.Lookahead == t {
		var buf string
		if _, err := fmt.Scanf("%s", &buf); err != nil {
			return err
		}
		p.Lookahead = buf
		return nil
	} else {
		return new(ParseError)
	}
}

func main() {
	var buf string
	if _, err := fmt.Scanf("%s", &buf); err != nil {
		panic(err)
	}
	p := PostfixParser{buf}

	if err := p.Expr(); err != nil {
		panic(err)
	}

	fmt.Println()
}
