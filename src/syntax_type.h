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

    void print(int indent)
    {
        cout << string(indent, ' ') << "user defined type: " << endl;
        id->print(indent + 2);
    }
};

class BuiltinType : public Type
{
    string typename_;

  public:
    BuiltinType(string _typename) : typename_(_typename) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "type: " << typename_ << endl;
    }
};

class ArrayType : public Type
{
    Type *elem_type;

  public:
    ArrayType(Type *_elem_type) : elem_type(_elem_type) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "array type of" << endl;
        elem_type->print(indent + 2);
    }
};

class RecordType : public Type
{
    Multi<Component> *components;

  public:
    RecordType(Multi<Component> *_components) : components(_components) {}

    void print(int indent)
    {
        cout << string(indent, ' ') << "record type" << endl;
        components->print(indent + 2);
    }
};

#endif