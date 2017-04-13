%{
#include <cstdio>
#include <iostream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

extern unsigned int linenum;
 
void yyerror(const char *s);

#define YYERROR_VERBOSE

/*class NodeProgram {}
class NodeExprList {}
class NodeExpr {}
class NodeNumber {}*/
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	int ival;
	//float fval;
	//char *sval;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <ival> INT
%token PLUS
%token MINUS
%token SEMICOLON

%%

program:
	exprlist			{ cout << "Successfully compiled." << endl; }

exprlist:
	exprlist expr SEMICOLON		{}
	| expr SEMICOLON		{}

expr:
	INT PLUS INT			{ cout << "Found expr: " << $1 << '+' << $3 << endl; }
	| INT MINUS INT			{ cout << "Found expr: " << $1 << '+' << $3 << endl; }

%%

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
	
}

void yyerror(const char *s) {
	cout << "Parse error!  Message: " << s << endl << "Found at line " << linenum << "." << endl;
	// might as well halt now:
	exit(-1);
}
