all: blre
# bytecode lang runtime environment

clean:
	rm -f *.o
	rm -f blre

##

main.o: main.c
	gcc -c	main.c	-o main.o

blre: main.o
	gcc main.o -o blre
