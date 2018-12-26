#ifndef _W_EXPRESS_
#define _W_EXPRESS_

#include <iostream>
#include <string>
#include "syntax_middle.h"

using namespace std;

class StrWExp : public WExp
{
    String *s;

  public:
    StrWExp(String *_s) : s(_s) {}

    void print(int Indentation)
    {
        s->print(Indentation);
    }
};

class ExpWExp : public WExp
{
    Exp *exp;

  public:
    ExpWExp(Exp *_exp) : exp(_exp) {}

    void print(int Indentation)
    {
        exp->print(Indentation);
    }
};

#endif
