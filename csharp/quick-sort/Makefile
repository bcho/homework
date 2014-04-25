.PHONY: clean

TARGET=exe
FILES=\
      ISortAlgorithm.cs \
      ISortAlgorithmSnapShot.cs \
      ISortAlgorithmSnapShotXML.cs \
      ISortAlgorithmSnapShotsXML.cs \
      Color.cs \
      DataScale.cs \
      SortAlgorithmSnapShot.cs \
      QuickSort.cs \
      QuickSortSnapShotXML.cs \
      QuickSortSnapShotsXML.cs \
      Application.cs

QuickSort.exe: $(FILES)
	dmcs -target:$(TARGET) -out:QuickSort.exe $(FILES)

clean:
	rm -f *.exe
