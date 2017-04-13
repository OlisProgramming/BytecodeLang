%{
#include <cstdio>
#include <iostream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

#include "nodes.h"
extern unsigned int linenum;
 
void yyerror(const char *s);

#define YYERROR_VERBOSE

NodeProgram* program;

%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	int ival;
	Node* nodeval;
	//float fval;
	//char *sval;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token SEMICOLON
%token PLUS
%token MINUS
%token MUL
%token DIV

%type <nodeval> program exprlist expr expr_muldiv arithmetic_unit  // use nodeval from the union as result of these expressions

%%

program:
	exprlist			{ $$ = program = new NodeProgram((NodeExprList*)$1); cout << "Successfully compiled." << endl; }

exprlist:
	exprlist expr SEMICOLON		{
		if ($1->getSymbol() == "exprlist") {
			((NodeExprList*)$1)->addChild($2); $$ = $1;
		} else { $$ = new NodeExprList($1, $2); }  // To flatten the exprlist binary tree into a single exprlist.
	}

	| expr SEMICOLON		{ $$ = new NodeExprList($1); }

expr:
	expr	PLUS	expr_muldiv	{ $$ = new NodePlus($1, $3); }
	| expr	MINUS	expr_muldiv	{ $$ = new NodeMinus($1, $3); }
	| expr_muldiv			{ $$ = $1; }

expr_muldiv:
	expr_muldiv	MUL	arithmetic_unit		{ $$ = new NodeMul($1, $3); }
	| expr_muldiv	DIV	arithmetic_unit		{ $$ = new NodeDiv($1, $3); }
	| arithmetic_unit				{ $$ = $1; }
	

arithmetic_unit:
	INT				{ $$ = new NodeNumeric($1); }

%%

#include <fstream>

int main(int, char**) {
	// open a file handle to a particular file:
	FILE *myfile = fopen("program.txt", "r");
	// make sure it is valid:
	if (!myfile) {
		return -1;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;
	
	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));

	ofstream dotfile("graph.dot");
	dotfile << "digraph {\n" << program->getDotCommand("root") << "}\n";
	dotfile.close();

	system("dot -Tpng -Efontname=Roboto -Nfontname=Roboto graph.dot -o graph.png");
	
}

void yyerror(const char *s) {
	cout << "Parse error - " << s << endl << "Found at line " << linenum << "." << endl;
	// might as well halt now:
	exit(-1);
}
