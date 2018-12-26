#ifndef _MIDDLE_
#define _MIDDLE_

#include <iostream>
#include <string>
#include <vector>

#include "syntax_base.h"

using namespace std;

class Id : public Node
{
    string id;

  public:
    Id(const char *_id) : id(_id) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "identifier:" << id << endl;
    }
};

class Number : public Node
{
    string repr;

  public:
    Number(const char *_repr) : repr(_repr) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "number " << repr << endl;
    }
};

class Op : public Node
{
    string op;

  public:
    Op(const char *_op) : op(_op) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "operator " << op << endl;
    }
};

class String : public Node
{
    string s;

  public:
    String(const char *_s) : s(_s) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "string literal " << s << endl;
    }
};

template <class T>
class Multi : public Node
{
    vector<T *> nodes;

  public:
    bool empty()
    {
        return nodes.empty();
    }

    void add(T *n)
    {
        nodes.push_back(n);
    }

    void print(int Indentation)
    {
        for (typename vector<T *>::reverse_iterator it = nodes.rbegin(); it != nodes.rend(); it++)
        {
            (*it)->print(Indentation);
        }
    }
};

class Lvalue : public Node
{
};

class CompValue : public Node
{
    Id *id;
    Exp *exp;

  public:
    CompValue(Id *_id, Exp *_exp) : id(_id), exp(_exp) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "member" << endl;
        id->print(Indentation + 2);
        cout << string(Indentation, ' ') << "value" << endl;
        ((Node *)exp)->print(Indentation + 4);
    }
};

class ArrayValue : public Node
{
};

class Exp : public Node
{
};

class WExp : public Node
{
};

class Stat : public Node
{
};

class ElseIf : public Node
{
    Exp *cond;
    Multi<Stat> *then;

  public:
    ElseIf(Exp *_cond, Multi<Stat> *_then) : cond(_cond), then(_then) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "condition" << endl;
        cond->print(Indentation + 2);
        cout << string(Indentation, ' ') << "then" << endl;
        then->print(Indentation + 2);
    }
};

class VarDec : public Node
{
    Multi<Id> *ids;
    Type *type;
    Exp *exp;

  public:
    VarDec(Multi<Id> *_ids, Type *_type, Exp *_exp)
        : ids(_ids), type(_type), exp(_exp)
    {
    }

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "variable declaration" << endl;
        cout << string(Indentation + 2, ' ') << "variable names" << endl;
        ids->print(Indentation + 4);
        if (type)
        {
            cout << string(Indentation + 2, ' ') << "type" << endl;
            ((Node *)type)->print(Indentation + 4);
        }
        cout << string(Indentation + 2, ' ') << "initializer" << endl;
        exp->print(Indentation + 4);
    }
};

class Type : public Node
{
};

class Component : public Node
{
    Id *id;
    Type *type;

  public:
    Component(Id *_id, Type *_type) : id(_id), type(_type) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "component id" << endl;
        id->print(Indentation + 2);
        cout << string(Indentation, ' ') << "component type" << endl;
        type->print(Indentation + 2);
    }
};

class TypeDec : public Node
{
    Id *id;
    Type *type;

  public:
    TypeDec(Id *_id, Type *_type) : id(_id), type(_type) {}
    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "type declaration" << endl;
        id->print(Indentation + 2);
        type->print(Indentation + 2);
    }
};

class FPSec : public Node
{
    Multi<Id> *ids;
    Type *type_;

  public:
    FPSec(Multi<Id> *_ids, Type *_type)
        : ids(_ids), type_(_type)
    {
    }

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "identifiers" << endl;
        ids->print(Indentation + 2);
        cout << string(Indentation, ' ') << "type" << endl;
        type_->print(Indentation + 2);
    }
};

class ProcDec : public Node
{
    Id *id;
    Multi<FPSec> *fpsecs;
    Type *type;
    Body *body;

  public:
    ProcDec(Id *_id, Multi<FPSec> *_fpsecs, Type *_type, Body *_body)
        : id(_id), fpsecs(_fpsecs), type(_type), body(_body)
    {
    }

    void print(int ident)
    {
        cout << string(ident, ' ') << "procedure declaration" << endl;
        cout << string(ident + 2, ' ') << "id" << endl;
        id->print(ident + 4);
        if (fpsecs)
        {
            cout << string(ident + 2, ' ') << "formal parameters" << endl;
            fpsecs->print(ident + 4);
        }
        if (type)
        {
            cout << string(ident + 2, ' ') << "return type" << endl;
            type->print(ident + 4);
        }
        ((Node *)body)->print(ident + 4);
    }
};

class Dec : public Node
{
    string type;
    Multi<Node> *block;

  public:
    Dec(const char *_type, Multi<Node> *_block) : type(_type), block(_block) {}

    void print(int ident)
    {
        block->print(ident);
    }
};

class Body : public Node
{
    Multi<Dec> *decls;
    Multi<Stat> *stats;

  public:
    Body(Multi<Dec> *_decls, Multi<Stat> *_stats) : decls(_decls), stats(_stats) {}
    void print(int ident)
    {
        cout << string(ident, ' ') << "body" << endl;
        cout << string(ident + 2, ' ') << "declarations" << endl;
        decls->print(ident + 4);
        cout << string(ident + 2, ' ') << "statements" << endl;
        stats->print(ident + 4);
    }
};

class Program : public Node
{
    Body *body;

  public:
    Program(Body *_body) : body(_body) {}
    void print(int ident)
    {
        cout << string(ident, ' ') << "program" << endl;
        body->print(ident + 2);
    }
};

#endif