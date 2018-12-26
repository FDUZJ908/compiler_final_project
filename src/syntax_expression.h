#ifndef _EXPRESS_
#define _EXPRESS_

#include <iostream>
#include <string>
#include "syntax_middle.h"

using namespace std;

class NumberExp : public Exp
{
    Number *n;

  public:
    NumberExp(Number *_n) : n(_n) {}

    void print(int Indentation)
    {
        n->print(Indentation);
    }
};

class LvalueExp : public Exp
{
    Lvalue *lval;

  public:
    LvalueExp(Lvalue *_lval) : lval(_lval) {}

    void print(int Indentation)
    {
        lval->print(Indentation);
    }
};

class BinOpExp : public Exp
{
    Op *op;
    Exp *left;
    Exp *right;

  public:
    BinOpExp(Op *_op, Exp *_left, Exp *_right)
        : op(_op), left(_left), right(_right) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "binary operator expression" << endl;
        left->print(Indentation + 4);
        op->print(Indentation + 2);
        right->print(Indentation + 4);
    }
};

class ArrayExp : public Exp
{
    Id *id;
    Multi<ArrayValue> *vals;

  public:
    ArrayExp(Id *_id, Multi<ArrayValue> *_vals) : id(_id), vals(_vals) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "array expression" << endl;
        cout << string(Indentation + 2, ' ') << "array id" << endl;
        id->print(Indentation + 4);
        cout << string(Indentation + 2, ' ') << "values" << endl;
        vals->print(Indentation + 4);
    }
};

class UnaryOpExp : public Exp
{
    Op *op;
    Exp *exp;

  public:
    UnaryOpExp(Op *_op, Exp *_exp) : op(_op), exp(_exp) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "unary operator expression" << endl;
        op->print(Indentation + 2);
        exp->print(Indentation + 2);
    }
};

class CallExp : public Exp
{
    Id *id;
    Multi<Exp> *params;

  public:
    CallExp(Id *_id, Multi<Exp> *_params) : id(_id), params(_params) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "function call" << endl;
        cout << string(Indentation + 2, ' ') << "function id" << endl;
        id->print(Indentation + 4);
        if (params)
        {
            cout << string(Indentation + 2, ' ') << "parameters" << endl;
            params->print(Indentation + 4);
        }
        else
        {
            cout << string(Indentation + 2, ' ') << "no parameter" << endl;
        }
    }
};

class RecordExp : public Exp
{
    Id *id;
    Multi<CompValue> *vals;

  public:
    RecordExp(Id *_id, Multi<CompValue> *_vals) : id(_id), vals(_vals) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "record expression" << endl;
        cout << string(Indentation + 2, ' ') << "record id" << endl;
        id->print(Indentation + 4);
        cout << string(Indentation + 2, ' ') << "values" << endl;
        vals->print(Indentation + 4);
    }
};

#endif