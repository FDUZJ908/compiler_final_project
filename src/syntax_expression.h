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

    void print(int indent)
    {
        n->print(indent);
    }
};

class LvalueExp : public Exp
{
    Lvalue *lval;

  public:
    LvalueExp(Lvalue *_lval) : lval(_lval) {}

    void print(int indent)
    {
        lval->print(indent);
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

    void print(int indent)
    {
        cout << string(indent, ' ') << "binary operator expression" << endl;
        left->print(indent + 4);
        op->print(indent + 2);
        right->print(indent + 4);
    }
};

class ArrayExp : public Exp
{
    Id *id;
    Multi<ArrayValue> *vals;

  public:
    ArrayExp(Id *_id, Multi<ArrayValue> *_vals) : id(_id), vals(_vals) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "array expression" << endl;
        cout << string(indent + 2, ' ') << "array id" << endl;
        id->print(indent + 4);
        cout << string(indent + 2, ' ') << "values" << endl;
        vals->print(indent + 4);
    }
};

class UnaryOpExp : public Exp
{
    Op *op;
    Exp *exp;

  public:
    UnaryOpExp(Op *_op, Exp *_exp) : op(_op), exp(_exp) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "unary operator expression" << endl;
        op->print(indent + 2);
        exp->print(indent + 2);
    }
};

class CallExp : public Exp
{
    Id *id;
    Multi<Exp> *params;

  public:
    CallExp(Id *_id, Multi<Exp> *_params) : id(_id), params(_params) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "function call" << endl;
        cout << string(indent + 2, ' ') << "function id" << endl;
        id->print(indent + 4);
        if (params)
        {
            cout << string(indent + 2, ' ') << "parameters" << endl;
            params->print(indent + 4);
        }
        else
        {
            cout << string(indent + 2, ' ') << "no parameter" << endl;
        }
    }
};

class RecordExp : public Exp
{
    Id *id;
    Multi<CompValue> *vals;

  public:
    RecordExp(Id *_id, Multi<CompValue> *_vals) : id(_id), vals(_vals) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "record expression" << endl;
        cout << string(indent + 2, ' ') << "record id" << endl;
        id->print(indent + 4);
        cout << string(indent + 2, ' ') << "values" << endl;
        vals->print(indent + 4);
    }
};

#endif