#ifndef _LVALUE_
#define _LVALUE_


#include <iostream>
#include <string>
#include "syntax_middle.h"

using namespace std;

class IdLvalue : public Lvalue
{
    Id *id;

  public:
    IdLvalue(Id *_id) : id(_id) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "id lvalue" << endl;
        id->print(indent + 4);
    }
};

class ArrayLvalue : public Lvalue
{
    Lvalue *lval;
    Exp *exp;

  public:
    ArrayLvalue(Lvalue *_lval, Exp *_exp) : lval(_lval), exp(_exp) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "array lvalue" << endl;
        cout << string(indent + 2, ' ') << "array" << endl;
        lval->print(indent + 4);
        cout << string(indent + 2, ' ') << "index" << endl;
        ((Node *)exp)->print(indent + 4);
    }
};

class RecordLvalue : public Lvalue
{
    Lvalue *lval;
    Id *id;

  public:
    RecordLvalue(Lvalue *_lval, Id *_id) : lval(_lval), id(_id) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "record lvalue" << endl;
        cout << string(indent + 2, ' ') << "record" << endl;
        lval->print(indent + 4);
        cout << string(indent + 2, ' ') << "member" << endl;
        id->print(indent + 4);
    }
};

#endif