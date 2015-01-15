.PHONY: preview-lab

FLAGS=-shell-escape

preview-lab: lab.pdf
	chromium $^

%.pdf: %.tex
	xelatex $(FLAGS) $^


clean:
	rm -rf *.log *.pdf *.aux
