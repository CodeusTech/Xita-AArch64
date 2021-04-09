/*
  addition.h
  Codeus Tech
  Authored on   April 28, 2020
  Last Modified April 28, 2020
*/

/*
  Contains structure/definitions for handling addition operator in XCS
*/

#pragma once

#include <xcs/std/includes.h>

#include <xcs/regstack/structs.h>
#include "../structs.h"

/*
  1.a) Addition Operator  --  (+)
*/
class AdditionOperator : public Operator
{
private:
  
public:
  AdditionOperator(OperatorManager*);
  char* resolve(RegisterStack* rs) override;
  ErrorCode override(TypeID rtn_type, TypeID left, TypeID right);
};




/*
  Constructors
*/
AdditionOperator::AdditionOperator(OperatorManager* manager) : Operator(manager)
{

  op = strdup(string("(+)").c_str());
  is_communitive = true;
}


/*
  Resolve Addition
*/
char* AdditionOperator::resolve(RegisterStack* rs)
{
  /*
    Get top 2 registers
    Add together (according to type sizes)
  */

  char* top = get_reg(rs->top(), 32);
  char* sec = get_reg(rs->sec(), 32);

  char* str = (char*) malloc(50);
  sprintf(str, "  add   %s, %s, %s", sec, sec, top);

  free(top);
  free(sec);

  return str;
} 

ErrorCode AdditionOperator::override(TypeID rtn_type, TypeID left, TypeID right)
{
  TypeID* tids = (TypeID*) malloc(2*sizeof(TypeID));

  tids[0] = left;
  tids[1] = right;

  operands.push_back(Operand(rtn_type, tids));
  return SUCCESS;
}