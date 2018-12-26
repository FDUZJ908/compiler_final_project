#ifndef _TYPE_
#define _TYPE_

#include <iostream>
#include <string>
#include "syntax_middle.h"

using namespace std;


class UserType : public Type
{
    Id *id;

  public:
    UserType(Id *_id) : id(_id) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "user defined type: " << endl;
        id->print(Indentation + 2);
    }
};

class BuiltinType : public Type
{
    string typename_;

  public:
    BuiltinType(string _typename) : typename_(_typename) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "type: " << typename_ << endl;
    }
};

class ArrayType : public Type
{
    Type *elem_type;

  public:
    ArrayType(Type *_elem_type) : elem_type(_elem_type) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "array type of" << endl;
        elem_type->print(Indentation + 2);
    }
};

class RecordType : public Type
{
    Multi<Component> *components;

  public:
    RecordType(Multi<Component> *_components) : components(_components) {}

    void print(int Indentation)
    {
        cout << string(Indentation, ' ') << "record type" << endl;
        components->print(Indentation + 2);
    }
};

#endif