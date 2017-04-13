all: parser_lexer program

main.o: main.cpp
	g++ -c main.cpp


program: main.o
	g++ -o program main.o -lfl

###

lex.yy.c: lexer.l
	flex lexer.l

parser.tab.c: parser.y
	bison -d parser.y

parser_lexer: parser.tab.c parser.tab.h lex.yy.c
	g++ lex.yy.c parser.tab.c -lfl -o parser_lexer

