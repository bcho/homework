.PHONY: clean

TARGET=exe
FILES=\
      Application.cs \
      ISortAlgorithm.cs \
      DataScale.cs \
      QuickSort.cs

QuickSort.exe: $(FILES)
	dmcs -target:$(TARGET) -out:QuickSort.exe $(FILES)

clean:
	rm -f *.exe
