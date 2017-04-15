all: blre
# bytecode lang runtime environment

clean:
	rm -f *.o
	rm -f blre

##

main.o: main.c
	gcc -c -g	main.c	-o main.o

blre: main.o
	gcc -g		main.o	-o blre
