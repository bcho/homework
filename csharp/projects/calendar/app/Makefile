.PHONY: all test clean

SRC := ./src
BUILD := .

NODE_MODS := ./node_modules


all: compile-js compile-scss

include src/js/build.mk
include src/scss/build.mk

test: test-js

clean: clean-js clean-scss
