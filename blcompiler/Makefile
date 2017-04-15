all: blcompiler
# blcompiler = bytecode lang compiler
# blre = bytecode lang runtime environment

clean:
	rm -f *.o
	rm -f *.dot
	rm -f *.png
	rm -f lex.yy.c
	rm -f parser.tab.*
	rm -f blcompiler

###

lex.yy.c: lexer.l nodes.h
	flex lexer.l

parser.tab.c: parser.y nodes.h
	bison -d parser.y

lexer.o: parser.tab.c lex.yy.c
	g++ -c	lex.yy.c		-std=c++11	-o lexer.o

parser.o: parser.tab.c
	g++ -c	parser.tab.c		-std=c++11	-o parser.o

main.o: main.cpp nodes.h parser.h bytecode_generator.h
	g++ -c	main.cpp		-std=c++11	-o main.o

bytecode_generator.o: bytecode_generator.h bytecode_generator.cpp ../types.h ../commands.h
	g++ -c bytecode_generator.cpp	-std=c++11	-o bytecode_generator.o

blcompiler: lexer.o parser.o main.o bytecode_generator.o
	g++	lexer.o parser.o main.o bytecode_generator.o \
		-lfl -std=c++11	-o blcompiler
	# g++ lex.yy.c parser.tab.c -lfl -std=c++11 -o program
