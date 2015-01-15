.PHONY: preview-project preview-lab

FLAGS=-shell-escape

preview-project: project.pdf
	chromium $^

preview-lab: lab.pdf
	chromium $^

%.pdf: %.tex
	xelatex $(FLAGS) $^


clean:
	rm -rf *.log *.pdf *.aux
