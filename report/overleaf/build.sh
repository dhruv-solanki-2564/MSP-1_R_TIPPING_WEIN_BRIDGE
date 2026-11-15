#!/bin/sh
# Build the report: pdflatex -> bibtex -> pdflatex x2
pdflatex -interaction=nonstopmode -halt-on-error main.tex >/dev/null || { tail -40 main.log; exit 1; }
bibtex main >/dev/null
pdflatex -interaction=nonstopmode main.tex >/dev/null
pdflatex -interaction=nonstopmode main.tex >/dev/null
grep -E "^! |Warning: (Reference|Citation)|Overfull \\\\hbox \([0-9]{2,}" main.log | sort | uniq -c | head -30
grep "Output written" main.log
