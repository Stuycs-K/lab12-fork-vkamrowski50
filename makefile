compile: main.o
	@gcc -Wall -o main main.o

main.o: main.c
	@gcc -c main.c

run: main
	@./main

clean:
	@rm -f *.o main
