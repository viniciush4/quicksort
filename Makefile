
all: compila clean executa

compila:
	gcc main.c -o main
	
clean:
	rm -rf *.o *.log *.aux

documentacao:
	pdflatex artigo.tex
	
executa:
	./main 1000 1000 5000 5
