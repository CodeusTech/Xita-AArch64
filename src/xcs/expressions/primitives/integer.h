/*
  integer.h
  Codeus Tech
  Authored on   April 22, 2020
  Last Modified April 22, 2020
*/

/*
  Contains structures/implementations for XCS integer primitives


  TABLE OF CONTENTS
  =================
  1.) Initialize Integer Primitives
  2.) Push Integer Primitive
*/

#pragma once

#include <xcs/std/includes.h>
#include <xcs/context/manager.h>

extern ContextManager context;


/*
  Initialize Integer Primitives
*/

ErrorCode initializeIntegerPrimitives()
{
  char* name = (char*) malloc(50);

  sprintf(name, "int"); context.declareType(name, 4);
  sprintf(name, "Int"); context.declareTypeConstructor(name);

  sprintf(name, "u8"); context.declareType(name, 1);
  sprintf(name, "U8"); context.declareTypeConstructor(name);
  sprintf(name, "i8"); context.declareType(name, 1);
  sprintf(name, "I8"); context.declareTypeConstructor(name);
  sprintf(name, "u16"); context.declareType(name, 2);
  sprintf(name, "U16"); context.declareTypeConstructor(name);
  sprintf(name, "i16"); context.declareType(name, 2);
  sprintf(name, "I16"); context.declareTypeConstructor(name);
  sprintf(name, "u32"); context.declareType(name, 4);
  sprintf(name, "U32"); context.declareTypeConstructor(name);
  sprintf(name, "i32"); context.declareType(name, 4);
  sprintf(name, "I32"); context.declareTypeConstructor(name);
  sprintf(name, "u64"); context.declareType(name, 8);
  sprintf(name, "U64"); context.declareTypeConstructor(name);
  sprintf(name, "i64"); context.declareType(name, 8);
  sprintf(name, "I64"); context.declareTypeConstructor(name);

  free(name);
  return SUCCESS;
}


/*
  2.) Push Integer Primitive
*/


/*
  pushInteger(value)

  Returns:
    0, if Successful

*/
ErrorCode pushInteger(Arbitrary value)
{
  TypeID tid = context.LastType();
  int bytes = 0;
  char suffix;

  switch(tid)
  {
    case 1: //  a
      context.LastType(TYPE_INTEGER);
    case 2: // Int 
    case 7: //  U32
    case 8: //  I32
      bytes = 4;
      suffix = ' ';
      break;
    case 3: //  U8
    case 4: //  I8
      bytes = 4;
      suffix = 'b';
      break;
    case 5: //  U16
    case 6: //  I16
      bytes = 4;
      suffix = 'h';
      break;
    case 9: //  U64
    case 10://  I64
      bytes = 8;
      suffix = 'd';
      break;
    default:
      yyerror("Attempted to add non-integer data casted as integer type");
      return 1;
  }

  //  Always push into 64-Bit Register (in case of type casting)
  char* reg = get_reg(context.rsPush(tid), bytes*8);

  char* str = (char*) malloc(50);
  sprintf(str, "  mov%c  %s, #%lld", suffix, reg, (long long) value);
  context.addInstruction(str);

  std::string sLog = string(context.resolveTypeIdentifier(context.LastType())) + " pushed into register: " + std::to_string(context.rsTop());
  l.log('d', "RegStack", sLog);

  free(str);
  free(reg);

  //  Reset Type for next Expression
  context.LastType(TYPE_ARBITRARY);

  return SUCCESS;
}

