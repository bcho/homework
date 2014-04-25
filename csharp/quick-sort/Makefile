.PHONY: clean

TARGET=exe
FILES=\
      ISortAlgorithm.cs \
      ISortAlgorithmSnapShot.cs \
      SortAlgorithmSnapShot.cs \
      DataScale.cs \
      QuickSort.cs \
      Application.cs \

QuickSort.exe: $(FILES)
	dmcs -target:$(TARGET) -out:QuickSort.exe $(FILES)

clean:
	rm -f *.exe
