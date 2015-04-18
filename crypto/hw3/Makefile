.PHONY: build compile-coffee clean

COFFEE=./node_modules/coffee-script/bin/coffee
COFFEE_FLAGS=--bare --compile


build: clean compile-coffee


compile-coffee: rsa.js rsa.test.js


%.js: %.coffee
	@$(COFFEE) $(COFFEE_FLAGS) $^

clean:
	@rm -f *.js
