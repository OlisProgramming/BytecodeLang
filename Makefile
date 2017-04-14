all: program

clean:
	rm *.o
	rm *.dot
	rm *.png
	rm lex.yy.c
	rm parser.tab.*
	rm program

###

lex.yy.c: lexer.l nodes.h
	flex lexer.l

parser.tab.c: parser.y nodes.h
	bison -d parser.y

lexer.o: parser.tab.h lex.yy.c
	g++ -c	lex.yy.c		-std=c++11	-o lexer.o

parser.o: parser.tab.c parser.tab.h
	g++ -c	parser.tab.c		-std=c++11	-o parser.o

main.o: main.cpp nodes.h
	g++ -c	main.cpp		-std=c++11	-o main.o

program: lexer.o parser.o main.o
	g++	lexer.o parser.o main.o \
		-lfl -std=c++11	-o program
	# g++ lex.yy.c parser.tab.c -lfl -std=c++11 -o program

