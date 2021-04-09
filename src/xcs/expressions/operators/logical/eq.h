/*
  eq.h (Logical)
  Codeus Tech
  Authored on   April 29, 2020
  Last Modified April 29, 2020
*/

/*
  Contains structure/definitions for 'Equal To', 'Not Equal To' Operations 
*/

#pragma once

#include <xcs/std/includes.h>

#include "../structs.h"


class EqualToOperator : public Operator
{


public:

  EqualToOperator(OperatorManager* manager) : Operator(manager)
  { }

  char* resolve(RegisterStack* rs) override;

};


class NotEqualOperator : public Operator
{


public:

  NotEqualOperator(OperatorManager* manager) : Operator(manager)
  { }

  char* resolve(RegisterStack* rs) override;
};


class LogicalNotOperator : public Operator
{


public:

  LogicalNotOperator(OperatorManager* manager) : Operator(manager) 
  { }

  char* resolve(RegisterStack* rs) override
  {
    //  STUB STUB STUB  (TODO: IMPLEMENT THIS!!!)
    char* top = get_reg(rs->top(), 32);
    char* sec = get_reg(rs->sec(), 32);

    //  STUB:  Needs to be rebuilt using previous implementation.
    char* str = (char*) malloc(50);
    sprintf(str, "  cmp  %s, %s", sec, top);

    l.log('D', "Operators", "Resolved Logical 'Not' Operation");

    free(top);
    free(sec);

    return str;
  }

};

