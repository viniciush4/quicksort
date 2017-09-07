
all: compila clean executa

compila:
	gcc main.c -o main
	
clean:
	rm -rf *.o *.log *.aux

executa:
	./main 1000 1000 100000 100
