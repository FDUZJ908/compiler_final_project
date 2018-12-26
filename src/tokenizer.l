%{
#include <iostream>
#include <cstdio>
#include "tokenizer.h"
#include "syntax.h"
using namespace std;
#define YY_DECL extern "C" int yylex()
#define YYSTYPE Node*
int find_token_code (char* token_buffer);

#include "main.tab.h" 


int row = 1, col = 1;
const int tab = 4;

%}

types	INTEGER|REAL|STRING
keywords	AND|OR|ELSIF|LOOP|PROGRAM|VAR|ARRAY|END|MOD|READ|WHILE|BEGIN|EXIT|NOT|RECORD|WRITE|BY|FOR|OF|RETURN|DIV|IF|THEN|DO|IN|OUT|TO|ELSE|IS|PROCEDURE|TYPE
nums	[0-9]
letters	[A-Za-z]
operators	\+|\-|\*|\/|<|<=|>|>=|=|<>
assign :=
delimiters	:|;|,|\.|\(|\)|\[|\]|\{|\}|\[<|>\]|\\

%%
\(\*.*\*\) {
	col += strlen(yytext);
}
[ ] {
	col += 1;
}
[\t] {
	col = ((col - 1) / tab + 1)  * tab + 1;
}
[\n] {
	col = 1;
	row += 1;
}
\"[^\"]*\" {
    yylval = new String(yytext);
	col += strlen(yytext);
    return STRING;
}
{types} {
	col += strlen(yytext);
    yylval = new BuiltinType(yytext);
    return TYPES;
}
{keywords} {
	col += strlen(yytext);
    return find_token_code(yytext);
}
{nums}+ {
	col += strlen(yytext);
    yylval = new Number(yytext);
    return  INTEGER;
}
{nums}+\.{nums}* {
	col += strlen(yytext);
    yylval = new Number(yytext);
    return REAL;
}
{letters}({letters}|{nums})* {
	col += strlen(yytext);
    yylval = new Id(yytext);
    return IDENTIFIER;
}
{operators} {
	col += strlen(yytext);
    yylval = new Op(yytext);
    return OPERATOR;
}
{assign} {
   col += strlen(yytext);
   return find_token_code(yytext);
}
{delimiters} {
	col += strlen(yytext);
    return find_token_code(yytext);
}

%%

int check_string(char *s) {
  int i = 0;
  if (strlen(s) > 255)
    return STR_OVER_LONG;
  else {
    for (i = 0; i < strlen(s); ++i)
      if (s[i] < 32)
        return UNEXPECTED_WORD;
    return 0;
  }
}


int check_integer(char* int_s) {
  int i = 0;
  if (strlen(int_s) > strlen(MAX_INT))
    return INT_OVERFLOW;
  else if (strlen(int_s) == strlen(MAX_INT)) {
    for (i = 0; i < strlen(int_s); ++i)
      if (int_s[i] > MAX_INT[i])
        return INT_OVERFLOW;
      else 
        if (int_s[i] < MAX_INT[i])
            return 0;
  }
  return 0;
}

