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

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "id lvalue" << endl;
        id->print(Indentation + 4);
    }
};

class ArrayLvalue : public Lvalue
{
    Lvalue *lval;
    Exp *exp;

  public:
    ArrayLvalue(Lvalue *_lval, Exp *_exp) : lval(_lval), exp(_exp) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "array lvalue" << endl;
        cout << string(Indentation + 2, ' ') << "array" << endl;
        lval->print(Indentation + 4);
        cout << string(Indentation + 2, ' ') << "index" << endl;
        ((Node *)exp)->print(Indentation + 4);
    }
};

class RecordLvalue : public Lvalue
{
    Lvalue *lval;
    Id *id;

  public:
    RecordLvalue(Lvalue *_lval, Id *_id) : lval(_lval), id(_id) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "record lvalue" << endl;
        cout << string(Indentation + 2, ' ') << "record" << endl;
        lval->print(Indentation + 4);
        cout << string(Indentation + 2, ' ') << "member" << endl;
        id->print(Indentation + 4);
    }
};

#endif