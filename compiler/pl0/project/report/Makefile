.PHONY: preview clean

TARGET=lab.pdf
PARTIALS=cover.tex
FLAGS=-shell-escape

preview: $(TARGET)
	xpdf $^

%.pdf: %.tex $(PARTIALS)
	xelatex $(FLAGS) $^

clean:
	rm -rf *.log *.pdf *.aux
