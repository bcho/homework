.PHONY: preview clean

preview: report.pdf
	xdg-open report.pdf


report.pdf: report.tex title.tex src/*
	xelatex report.tex


clean:
	rm -v *.aux *.log *.toc *.ind *.gls *.glo *.idx *.ilg *.out *.bbl *.thm *.blg *.lot *.lof *~
