all: main

main: lab1.o complex.o vector.o number.o matrix.o tests.o
	gcc *.o -o main

complex.o: complex.c
	gcc -c complex.c

number.o: number.c
	gcc -c number.c

vector.o: vector.c	
	gcc -c vector.c

matrix.o: matrix.c
	gcc -c matrix.c

lab1.o: lab1.c
	gcc -c lab1.c

tests.o: tests.c
	gcc -c tests.c


clean:
	rm -rf *.o main
