%{
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

#include "syntax.h"

extern "C" int yylex();
extern "C" FILE *yyin;
extern "C" int row, col;
extern "C" char* yytext;

void yyerror(const char *s);

#define YYSTYPE Node*
%}

%token TYPES
%token INTEGER
%token REAL
%token OPERATOR
%token STRING
%token IDENTIFIER
%token-table 

%define parse.error verbose 
%%

program: "PROGRAM" "IS" body ";" 
{ 
  Program* prog = new Program((Body*)$3);
  prog->print(0);
  $$ = prog;
};

body: declarationBlock "BEGIN" statementBlock "END" 
{ 
  $$ = new Body((Multi<Dec>*)$1, (Multi<Stat>*)$3); 
};

declarationBlock: declaration declarationBlock 
{ 
  ((Multi<Dec>*)$2)->add((Dec*)$1); 
  $$=$2; 
}
| { $$ = new Multi<Dec>(); }  ;

statementBlock: statement statementBlock 
{
  ((Multi<Stat>*)$2)->add((Stat*)$1);
  $$ = $2;
}
| { $$ = new Multi<Stat>(); } ;

declaration: "VAR" varDecBlock 
{
  $$ = new Dec("var", (Multi<Node>*)$2);
}
| "TYPE" typeDecBlock
{
  $$ = new Dec("type", (Multi<Node>*)$2);
}
| "PROCEDURE" procDecBlock 
{
  $$ = new Dec("procedure", (Multi<Node>*)$2);
};

varDecBlock: varDec varDecBlock 
{
  ((Multi<VarDec>*)$2)->add((VarDec*)$1);
  $$ = $2;
}
| varDec 
{
  Multi<VarDec>* v = new Multi<VarDec>();
  v->add((VarDec*)$1);
  $$ = v;
};

typeDecBlock: typeDec typeDecBlock 
{
  ((Multi<TypeDec>*)$2)->add((TypeDec*)$1);
  $$ = $2;
}
| typeDec
{
  Multi<TypeDec>* v = new Multi<TypeDec>();
  v->add((TypeDec*)$1);
  $$ = v;
};

procDecBlock: procDec procDecBlock 
{
  ((Multi<ProcDec>*)$2)->add((ProcDec*)$1);
  $$ = $2;
}
| procDec
{
  Multi<ProcDec>* v = new Multi<ProcDec>();
  v->add((ProcDec*)$1);
  $$ = v;
};

varDec: idBlock typeOpt ":=" exp ";" 
{
  $$ = new VarDec((Multi<Id>*)$1, (Type*)$2, (Exp*)$4);
};

idBlock: IDENTIFIER "," idBlock 
{
  ((Multi<Id>*)$3)->add((Id*)$1);
  $$ = $3;
}
| IDENTIFIER
{
  Multi<Id>* v = new Multi<Id>();
  v->add((Id*)$1);
  $$ = v;
};

typeOpt: ":" type 
{
  $$ = $2;
}
| { $$ = NULL; };

typeDec: IDENTIFIER "IS" type ";" 
{
  $$ = new TypeDec((Id*)$1, (Type*)$3);
};

procDec: IDENTIFIER formalParams typeOpt "IS" body ";" 
{
  $$ = new ProcDec((Id*)$1, (Multi<FPSec>*)$2, (Type*)$3, (Body*)$5);
};

type: IDENTIFIER 
{
  $$ = new UserType((Id*)$1);
}
| TYPES 
{
  $$ = $1;
}
| "ARRAY" "OF" type 
{
  $$ = new ArrayType((Type *)$3);
}
| "RECORD" componentBlock "END"
{
  $$ = new RecordType((Multi<Component>*)$2);
};

componentBlock: component componentBlock 
{
  ((Multi<Component>*)$2)->add((Component*)$1);
  $$ = $2;
}
| component 
{
  Multi<Component>* v = new Multi<Component>();
  v->add((Component*)$1);
  $$ = v;
};

component: IDENTIFIER ":" type ";"
{
  $$ = new Component((Id*)$1, (Type*)$3);
};

formalParams: "(" fpSectionBlock ")"  { $$ = $2; } 
| "(" ")"
{
  $$ = NULL;
};

fpSectionBlock: fp_section ";" fpSectionBlock 
{
  ((Multi<FPSec>*)$3)->add((FPSec*)$1);
  $$ = $3;
}
| fp_section
{
  Multi<FPSec>* v = new Multi<FPSec>;
  v->add((FPSec*)$1);
  $$ = v;
};

fp_section: idBlock ":" type
{
  $$ = new FPSec((Multi<Id>*)$1, (Type*)$3);
};

statement: 
 lvalue ":=" exp ";" 
 {
   $$ = new AssignStat((Lvalue*)$1, (Exp*)$3);
 } 
|
 IDENTIFIER actualParams ";" 
{
  $$ = new CallStat((Id*)$1, (Multi<Exp>*)$2);
}
|
 "READ" "(" lvalueBlock ")" ";" 
{ 
  $$ = new RStat((Multi<Lvalue>*)$3);
}
|
 "WRITE" wParams ";" 
{
  $$ = new WStat((Multi<WExp>*)$2);
}
|
 "IF" exp "THEN" statementBlock elseIfBlock elseOpt "END" ";" 
{
  $$ = new IfStat((Exp*)$2, (Multi<Stat>*)$4, (Multi<ElseIf>*)$5, 
                  (Multi<Stat>*)$5);
}
|
 "WHILE" exp "DO" statementBlock "END" ";"
{
  $$ = new WhileStat((Exp*)$2, (Multi<Stat>*)$4);
}
|
 "LOOP" statementBlock "END" ";" 
{
  $$ = new LoopStat((Multi<Stat>*)$2);
}
|
 "FOR" IDENTIFIER ":=" exp "TO" exp byOpt "DO" statementBlock "END" ";" 
{
  $$ = new ForStat((Id*)$2, (Exp*)$4, (Exp*)$6, (Exp*)$7, (Multi<Stat>*)$9);
}
|
 "EXIT" ";" 
{
  $$ = new ExitStat();
}
|
 "RETURN" expOpt ";"
{
  $$ = new ReturnStat((Exp*)$2);
}
 ;

byOpt: "BY" exp
{ $$ = $2; }  
| { $$ = NULL; };

elseIfBlock: "ELSIF" exp "THEN" statementBlock elseIfBlock 
{
  Multi<ElseIf>* v = (Multi<ElseIf>*)$5;
  ElseIf* s = new ElseIf((Exp*)$2, (Multi<Stat>*)$4);
  v->add(s);
  $$ = v;
}
|
{
  $$ = new Multi<ElseIf>();
};
elseOpt: "ELSE" statementBlock 
{
  { $$ = $2; }
}
| { $$ = NULL;  } ;

lvalueBlock: lvalue "," lvalueBlock 
{
  Multi<Lvalue>* v = (Multi<Lvalue>*)$3;
  v->add((Lvalue*)$1);
  $$ = v;
}
| lvalue
{
  Multi<Lvalue>* v = new Multi<Lvalue>();
  v->add((Lvalue*)$1);
  $$ = $1;
};

wParams:  "(" wExpBlock ")" 
{
  $$ = $2;
}
| "(" ")"
{
  $$ = NULL;
};
wExpBlock: wExp "," wExpBlock 
{
  Multi<WExp>* v = (Multi<WExp>*)$3;
  v->add((WExp*)$1);
  $$ = v;
}
| wExp
{
  Multi<WExp>* v = new Multi<WExp>();
  v->add((WExp*)$1);
  $$ = v;
};

wExp: STRING 
{
  $$ = new StrWExp((String*)$1);
}                        
| exp 
{
  $$ = new ExpWExp((Exp*)$1);
};

exp: number { $$ = $1; }| 
lvalue { $$ = new LvalueExp((Lvalue*)$1); }| 
"(" exp ")" { $$ = $2; }| 
unaryOp exp { $$ = new UnaryOpExp((Op*)$1, (Exp*)$2); } |
exp binaryOp exp { $$ = new BinOpExp((Op*)$2, (Exp*)$1, (Exp*)$3); } |
IDENTIFIER actualParams { $$ = new CallExp((Id*)$1, (Multi<Exp>*)$2); }|
IDENTIFIER compValues { $$ = new RecordExp((Id*)$1, (Multi<CompValue>*)$2); } |
IDENTIFIER arrayValues { $$ = new ArrayExp((Id*)$1, (Multi<ArrayValue>*)$2); };

expBlock: exp "," expBlock 
{
  Multi<Exp>* v = (Multi<Exp>*)$3;
  v->add((Exp*)$1);
  $$ = v;
}
| exp 
{
  Multi<Exp>* v = new Multi<Exp>();
  v->add((Exp*)$1);
  $$ = v;
};
expOpt: exp { $$=$1; }| {$$=NULL;};

lvalue: IDENTIFIER { $$ = new IdLvalue((Id*)$1); } |
lvalue "[" exp "]" { $$ = new ArrayLvalue((Lvalue*)$1, (Exp*)$3); } |
lvalue "." IDENTIFIER { $$ = new RecordLvalue((Lvalue*)$1, (Id*)$3); } ;

actualParams: "(" expBlock ")" { $$ = $2; } 
| "(" ")" { $$ = NULL; } ;

compValues: "{" compValueBlock "}" { $$ = $2; };
compValueBlock: IDENTIFIER ":=" exp ";" compValueBlock 
{
  Multi<CompValue>* v = (Multi<CompValue>*)$5;
  v->add(new CompValue((Id*)$1, (Exp*)$3));
  $$ = v;
}
| IDENTIFIER ":=" exp
{
   Multi<CompValue>* v = new Multi<CompValue>();
   v->add(new CompValue((Id*)$1, (Exp*)$3));
   $$ = v;
};

arrayValues: "[<" arrayValueBlock ">]" { $$ = $2; };

arrayValueBlock: arrayValue "," arrayValueBlock 
{
  Multi<ArrayValue>* v = (Multi<ArrayValue>*)$3;
  v->add((ArrayValue*)$1);
  $$ = v;
}
| arrayValue
{
  Multi<ArrayValue>* v = new Multi<ArrayValue>();
  v->add((ArrayValue*)$1);
  $$ = v;
};

arrayValue: exp "OF" exp 
{ $$ = new OfArrayValue((Exp*)$1, (Exp*)$3); }
| exp { $$ = new SimpleArrayValue((Exp*)$1); };

number: REAL { $$ = new NumberExp((Number*)$1); } 
| INTEGER { $$ = new NumberExp((Number*)$1); } ;

unaryOp:  OPERATOR { $$ = $1; } | "NOT" { $$ = new Op("NOT"); };

binaryOp: OPERATOR { $$ = $1; } 
| "DIV" { $$ = new Op("DIV"); }
| "MOD" { $$ = new Op("MOD"); } 
| "OR"  { $$ = new Op("OR"); }
| "AND" { $$ = new Op("AND"); };


%%

int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "Need a file" << endl;
    return -1;
  }

	FILE *myfile = fopen(argv[1], "r");
	if (!myfile) {
		cout << "I can't open file!" << endl;
		return -1;
	}
	yyin = myfile;
	do {
		yyparse();
	} while (!feof(yyin));
	
}

void yyerror(const char *s) {
	cout  << "Error!" << endl
        << "Position: " << row << ":" << col << endl
        << "token: " << yytext << endl
        << "Message: " << s << endl;
	exit(-1);
}

int find_token_code (char* token_buffer) {
    int i;
    for (i = 0; i < YYNTOKENS; i++) {
        if (yytname[i] != 0
            && yytname[i][0] == '"'
            && ! strncmp (yytname[i] + 1, token_buffer,
                          strlen (token_buffer))
            && yytname[i][strlen (token_buffer) + 1] == '"'
            && yytname[i][strlen (token_buffer) + 2] == 0)
          break;
    }

    return  255+i;
}
