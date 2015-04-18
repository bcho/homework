.PHONY: build compile-coffee compile-nw clean

COFFEE=./node_modules/coffee-script/bin/coffee
COFFEE_FLAGS=--bare --compile
NODE=node


build: clean compile-coffee compile-nw


compile-coffee: rsa.js rsa.test.js app.js

compile-nw: compile-coffee
	@$(NODE) build.js


%.js: %.coffee
	@$(COFFEE) $(COFFEE_FLAGS) $^

clean:
	@rm -f rsa*.js app.js
