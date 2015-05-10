.PHONY: compile-scss clean-scss


SASS := sass
SASSFLAGS := --scss --sourcemap=inline
SCSS_SRC += $(SRC)/scss
SCSS_BUILD += $(BUILD)/css/


compile-scss: $(SCSS_SRC)
	@mkdir -p $(SCSS_BUILD)
	@$(SASS) $(SASSFLAGS) $(SCSS_SRC)/app.scss $(SCSS_BUILD)/app.css


clean-scss:
	@rm -rf $(SCSS_BUILD)
