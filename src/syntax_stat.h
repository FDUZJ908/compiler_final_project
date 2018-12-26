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

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "assignment statement" << endl;
        lvalue->print(Indentation + 2);
        cout << string(Indentation + 2, ' ') << "value" << endl;
        exp->print(Indentation + 4);
    }
};

class CallStat : public Stat
{
    Id *id;
    Multi<Exp> *params;

  public:
    CallStat(Id *_id, Multi<Exp> *_params) : id(_id), params(_params) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "function call statement" << endl;
        cout << string(Indentation + 2, ' ') << "function name" << endl;
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

class RStat : public Stat
{
    Multi<Lvalue> *lvalues;

  public:
    RStat(Multi<Lvalue> *_lvalues) : lvalues(_lvalues) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "read statement" << endl;
        lvalues->print(Indentation + 2);
    }
};

class WStat : public Stat
{
    Multi<WExp> *wParams;

  public:
    WStat(Multi<WExp> *_w_params) : wParams(_w_params) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "write statement" << endl;
        wParams->print(Indentation + 2);
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

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "if statement" << endl;
        cout << string(Indentation + 2, ' ') << "condition" << endl;
        cond->print(Indentation + 4);
        cout << string(Indentation + 2, ' ') << "then" << endl;
        then->print(Indentation + 4);
        if (elseif && !elseif->empty())
        {
            cout << string(Indentation + 2, ' ') << "elseif" << endl;
            elseif->print(Indentation + 4);
        }
        if (else_)
        {
            cout << string(Indentation + 2, ' ') << "else" << endl;
            else_->print(Indentation + 4);
        }
    }
};

class LoopStat : public Stat
{
    Multi<Stat> *body;

  public:
    LoopStat(Multi<Stat> *_body) : body(_body) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "loop" << endl;
        body->print(Indentation + 2);
    }
};

class WhileStat : public Stat
{
    Exp *cond;
    Multi<Stat> *body;

  public:
    WhileStat(Exp *_cond, Multi<Stat> *_body) : cond(_cond), body(_body){};

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "while loop" << endl;
        cout << string(Indentation + 2, ' ') << "condition expression" << endl;
        cond->print(Indentation + 4);
        cout << string(Indentation + 2, ' ') << "body" << endl;
        body->print(Indentation + 4);
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

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "for statement" << endl;

        cout << string(Indentation + 2, ' ') << "for variable" << endl;
        id->print(Indentation + 4);

        cout << string(Indentation + 2, ' ') << "from" << endl;
        from->print(Indentation + 4);

        cout << string(Indentation + 2, ' ') << "to" << endl;
        to->print(Indentation + 4);

        if (by)
        {
            cout << string(Indentation + 2, ' ') << "by" << endl;
            by->print(Indentation + 4);
        }

        cout << string(Indentation + 2, ' ') << "for body" << endl;
        body->print(Indentation + 4);
    }
};

class ReturnStat : public Stat
{
    Exp *val;

  public:
    ReturnStat(Exp *_val) : val(_val) {}
    void print(int Indentation)
    {
        if (val)
        {
            cout << string(Indentation, ' ') << "return value" << endl;
            val->print(Indentation + 4);
        }
        else
        {
            cout << string(Indentation, ' ') << "return statement" << endl;
        }
    }
};

class ExitStat : public Stat
{
  public:
    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "exit statement" << endl;
    }
};

#endif