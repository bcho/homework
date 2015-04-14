.PHONY: clean test

TARGET=exe
FILES=\
      	Assert.cs \
	BinaryTree.cs
CC=dmcs
MONO=mono


test: BinaryTree.exe
	@$(MONO) BinaryTree.exe test

run: BinaryTree.exe
	@$(MONO) BinaryTree.exe

BinaryTree.exe: $(FILES)
	@$(CC) -target:$(TARGET) -out:BinaryTree.exe $(FILES)

clean:
	rm -f *.exe
