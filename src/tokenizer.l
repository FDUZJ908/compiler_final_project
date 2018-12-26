%{
#include "syntax.h"
using namespace std;
#define YY_DECL extern "C" int yylex()
#define YYSTYPE Node*
int find_token_code (char* token_buffer);

#include "main.tab.h" 


int row = 1, col = 1;
const int tab = 4;

%}

types	    INTEGER|REAL|STRING
keywords	AND|OR|ELSIF|LOOP|PROGRAM|VAR|ARRAY|END|MOD|READ|WHILE|BEGIN|EXIT|NOT|RECORD|WRITE|BY|FOR|OF|RETURN|DIV|IF|THEN|DO|IN|OUT|TO|ELSE|IS|PROCEDURE|TYPE
nums	    [0-9]
letters	    [A-Za-z]
operators	\+|\-|\*|\/|<|<=|>|>=|=|<>
assign      :=
delimiters	:|;|,|\.|\(|\)|\[|\]|\{|\}|\[<|>\]|\\

%%
\(\*.*\*\) {
	col += strlen(yytext);
}
[ ] {
	col += 1;
}
[\t] {
	col = col + tab;
}
[\n] {
	col = 1;
	row += 1;
}
\"[^\"]*\" {
    if (strlen(yytext)>255)
        yylval = new String(("error! overflow "+to_string(row)+":"+to_string(col)).c_str());
    else
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
    try {
        stoi(yytext);
        yylval = new Number(yytext);
    } catch (exception e) {
        yylval = new Number(("error! overflow "+to_string(row)+":"+to_string(col)).c_str());
    }
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

