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

    void print(int indent)
    {
        ((Node *)left)->print(indent + 4);
        cout << string(indent + 2, ' ') << "of" << endl;
        ((Node *)right)->print(indent + 4);
    }
};

class SimpleArrayValue : public ArrayValue
{
    Exp *exp;

  public:
    SimpleArrayValue(Exp *_exp) : exp(_exp) {}

    void print(int indent)
    {
        ((Node *)exp)->print(indent);
    }
};

#endif