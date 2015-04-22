.PHONY: clean test run


TARGET=exe
FILES=ContactModel.cs \
      ContactModelManager.cs
CONTACT_FILES=$(FILES)
TEST_FILES=$(FILES) \
	   Assert.cs \
	   Tests.cs
CC=dmcs
MONO=mono

test: Tests.exe
	@$(MONO) Tests.exe
	@echo "all tests passed"

run: Contact.exe
	@$(MONO) Contact.exe

Contact.exe: $(CONTACT_FILES)
	@$(CC) -target:$(TARGET) -out:$@ $^

Tests.exe: $(TEST_FILES)
	@$(CC) -target:$(TARGET) -out:$@ $^
