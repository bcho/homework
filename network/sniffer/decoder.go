package main

import (
	"errors"
)

var errDecodeFailed = errors.New("decode failed")

type decodeFunc func([]byte) (Impl, decodeFunc, error)
