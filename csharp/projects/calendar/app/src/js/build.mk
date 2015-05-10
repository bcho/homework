.PHONY: compile-js clean-js test-js

BRO := $(NODE_MODS)/browserify/bin/cmd.js
BROFLAGS := -t babelify -t reactify -d

MOCHA := $(NODE_MODS)/mocha/bin/mocha
MOCHAFLAGS := --compilers js:babel/register \
    --require should \
    --recursive \
    --reporter dot \
    --ui bdd

JS_SRC += $(SRC)/js
JS_BUILD += $(BUILD)/js


compile-js: $(JS_SRC)
	@mkdir -p $(JS_BUILD)
	@$(BRO) $(BROFLAGS) $(JS_SRC)/app.js -o $(JS_BUILD)/app.js


clean-js:
	@rm -rf $(JS_BUILD)


test-js:
	@$(MOCHA) $(MOCHAFLAGS) $(JS_SRC)/test
