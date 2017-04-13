%{
#include <cstdio>
#include <iostream>
using namespace std;
#define YY_DECL extern "C" int yylex()

#include "parser.tab.h"  // to get the token types that we return

unsigned int linenum = 1;
%}
%%
[\w\t]			;
\n			{ ++linenum; }
\+			{ return PLUS; }
-			{ return MINUS; }
;			{ return SEMICOLON; }
[0-9]+			{ yylval.ival = atoi(yytext); return INT;  /* [a-zA-Z0-9]+		{
	yyerror("Do not use strings...yet");
	// we have to copy because we can't rely on yytext not changing underneath us:
	//yylval.sval = strdup(yytext);
	return INT;
}*/ }
%%
