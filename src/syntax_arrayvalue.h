#ifndef _ARRAY_VALUE_
#define _ARRAY_VALUE_

#include <iostream>
#include <string>
#include "syntax_middle.h"

using namespace std;

class OfArrayValue : public ArrayValue
{
    Exp *left;
    Exp *right;

  public:
    OfArrayValue(Exp *_left, Exp *_right) : left(_left), right(_right) {}

    void print(int Indentation)
    {
        ((Node *)left)->print(Indentation + 4);
        cout << string(Indentation + 2, ' ') << "of" << endl;
        ((Node *)right)->print(Indentation + 4);
    }
};

class SimpleArrayValue : public ArrayValue
{
    Exp *exp;

  public:
    SimpleArrayValue(Exp *_exp) : exp(_exp) {}

    void print(int Indentation)
    {
        ((Node *)exp)->print(Indentation);
    }
};

#endif