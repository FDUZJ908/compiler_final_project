#ifndef _STAT_
#define _STAT_

#include <iostream>
#include <string>
#include "syntax_middle.h"

using namespace std;

class AssignStat : public Stat
{
    Lvalue *lvalue;
    Exp *exp;

  public:
    AssignStat(Lvalue *_lvalue, Exp *_exp)
        : lvalue(_lvalue), exp(_exp)
    {
    }

    void print(int indent)
    {
        cout << string(indent, ' ') << "assignment statement" << endl;
        lvalue->print(indent + 2);
        cout << string(indent + 2, ' ') << "value" << endl;
        exp->print(indent + 4);
    }
};

class CallStat : public Stat
{
    Id *id;
    Multi<Exp> *params;

  public:
    CallStat(Id *_id, Multi<Exp> *_params) : id(_id), params(_params) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "function call statement" << endl;
        cout << string(indent + 2, ' ') << "function name" << endl;
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

class RStat : public Stat
{
    Multi<Lvalue> *lvalues;

  public:
    RStat(Multi<Lvalue> *_lvalues) : lvalues(_lvalues) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "read statement" << endl;
        lvalues->print(indent + 2);
    }
};

class WStat : public Stat
{
    Multi<WExp> *wParams;

  public:
    WStat(Multi<WExp> *_w_params) : wParams(_w_params) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "write statement" << endl;
        wParams->print(indent + 2);
    }
};

class IfStat : public Stat
{
    Exp *cond;
    Multi<Stat> *then;
    Multi<ElseIf> *elseif;
    Multi<Stat> *else_;

  public:
    IfStat(Exp *_cond, Multi<Stat> *_then, Multi<ElseIf> *_elseif, Multi<Stat> *_else)
        : cond(_cond), then(_then), elseif(_elseif), else_(_else)
    {
    }

    void print(int indent)
    {
        cout << string(indent, ' ') << "if statement" << endl;
        cout << string(indent + 2, ' ') << "condition" << endl;
        cond->print(indent + 4);
        cout << string(indent + 2, ' ') << "then" << endl;
        then->print(indent + 4);
        if (elseif && !elseif->empty())
        {
            cout << string(indent + 2, ' ') << "elseif" << endl;
            elseif->print(indent + 4);
        }
        if (else_)
        {
            cout << string(indent + 2, ' ') << "else" << endl;
            else_->print(indent + 4);
        }
    }
};

class LoopStat : public Stat
{
    Multi<Stat> *body;

  public:
    LoopStat(Multi<Stat> *_body) : body(_body) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "loop" << endl;
        body->print(indent + 2);
    }
};

class WhileStat : public Stat
{
    Exp *cond;
    Multi<Stat> *body;

  public:
    WhileStat(Exp *_cond, Multi<Stat> *_body) : cond(_cond), body(_body){};

    void print(int indent)
    {
        cout << string(indent, ' ') << "while loop" << endl;
        cout << string(indent + 2, ' ') << "condition expression" << endl;
        cond->print(indent + 4);
        cout << string(indent + 2, ' ') << "body" << endl;
        body->print(indent + 4);
    }
};

class ForStat : public Stat
{
    Id *id;
    Exp *from;
    Exp *to;
    Exp *by;
    Multi<Stat> *body;

  public:
    ForStat(Id *_id, Exp *_from, Exp *_to, Exp *_by, Multi<Stat> *_body)
        : id(_id), from(_from), to(_to), by(_by), body(_body)
    {
    }

    void print(int indent)
    {
        cout << string(indent, ' ') << "for statement" << endl;

        cout << string(indent + 2, ' ') << "for variable" << endl;
        id->print(indent + 4);

        cout << string(indent + 2, ' ') << "from" << endl;
        from->print(indent + 4);

        cout << string(indent + 2, ' ') << "to" << endl;
        to->print(indent + 4);

        if (by)
        {
            cout << string(indent + 2, ' ') << "by" << endl;
            by->print(indent + 4);
        }

        cout << string(indent + 2, ' ') << "for body" << endl;
        body->print(indent + 4);
    }
};

class ReturnStat : public Stat
{
    Exp *val;

  public:
    ReturnStat(Exp *_val) : val(_val) {}
    void print(int indent)
    {
        if (val)
        {
            cout << string(indent, ' ') << "return value" << endl;
            val->print(indent + 4);
        }
        else
        {
            cout << string(indent, ' ') << "return statement" << endl;
        }
    }
};

class ExitStat : public Stat
{
  public:
    void print(int indent)
    {
        cout << string(indent, ' ') << "exit statement" << endl;
    }
};

#endif