/*
  structs.h
  Codeus Tech
  Authored on   October 30, 2019
  Last Modified October 30, 2019
*/

/*
  Contains Data Structures used within XCS's Register Stack Infrastructure
*/

#ifndef REGSTACK_STRUCTS_H
#define REGSTACK_STRUCTS_H

//  Linux Libraries
#include <vector>

//  XCS Libraries
#include <xcs/std/includes.h>
#include <xcs/std/typedefs.h>
#include <xcs/std/optimize.h>
#include <xcs/utils/mangle.h>

using namespace std;

extern void yyerror(const char* str);

class RegisterStack
{
  vector<ADR> registers;
  vector<TypeID> types;
	


public:

//  CONSTRUCTORS
  RegisterStack() 
  {
    l.log('d', "RegStack", "Initialized New Register Stack");
  }


/*
  MUTATORS
*/
  ADR push(TypeID tid)
  {
    //  If all registers are in use, reroute to extended stack space
    if (registers.size() >= NUMBER_OF_ADRS) { return NUMBER_OF_ADRS + 1; } 
    //  TODO: FIX THE ABOVE LINE!!!

    //  Acquire a mangled random number in ADR range
    ADR check = (ADR) (get_mangle() % NUMBER_OF_ADRS) + 1;

    //  If the test register is not in use, add it to active ADRs vector
    while (isActive(check)) check = (ADR) (get_mangle() % NUMBER_OF_ADRS) + 1;

    //  If all else is kosher, Add the entry and type
    registers.push_back(check);
    types.push_back(tid);

    string str = "Pushed register " + to_string(check) + " with TypeID: " + to_string(tid);

    //l.log('D', "RegStack", str);

    return check;
  }

  /*
    duplicateTop() 
      Adds the top ADR/Type to the register stack again.
      This is used to correct subsequent automatic pop() operations.
  */
  ErrorCode duplicateTop()
  {
    registers.push_back(registers.back());
    types.push_back(types.back());

    return SUCCESS;
  }

  ADR merge(TypeID tid, ADR reg)
  {
    /*
      TODO: Check if 'reg' is already active
    */

    registers.push_back(reg);
    types.push_back(tid);

    return reg; //  Should return merged register (if 'reg' is active)
  }

  ErrorCode pop()
  {
    registers.pop_back();
    types.pop_back();
    return SUCCESS;
  }

  /*
    remove(from_top)
      This function removes the entry X places from top of the reg stack, then returns all entries above it to the stack.  
      If "from_top" == 0, it will remove the top entry of the stack; "from_top" == 1 will remove the second from top.
  */
  ErrorCode remove(int from_top)
  {
    vector<ADR> buffer_reg;
    vector<TypeID> buffer_type;

    //  Store registers/types to buffer
    for (int i = 0; i < from_top; ++i)
    {
      buffer_reg.push_back(registers.back()); registers.pop_back();
      buffer_type.push_back(types.back()); types.pop_back();
    }

    //  Remove Target Register
    registers.pop_back();
    types.pop_back();

    //  Restore Registers/types from buffer
    for (int i = 0; i < from_top; ++i)
    {
      registers.push_back(buffer_reg.back()); buffer_reg.pop_back();
      types.push_back(buffer_type.back()); buffer_type.pop_back();
    }

    return SUCCESS;
  }

  ErrorCode removeSec() { return remove(1); }


/*
  ACCESSORS
*/
  ADR from_top(int i) { return registers.at(registers.size()-(i+1)); }
  ADR top() { return registers.back(); }
  ADR sec() { return registers.at(registers.size()-2); }

  ADR from_top_type(int i) { return types.at(types.size()-(i+1)); }
  ADR top_type() { return types.back(); }
  ADR sec_type() { return types.at(types.size()-2); }

  unsigned int size() const { return registers.size(); }

  /*
    isActive(test)
      Returns true if the test ADR is already active
  */
  bool isActive(ADR test) const
  {
    for (unsigned long i = 0; i < registers.size(); i++)
      if ((registers[i]) == (test)) return true;
    return false;
  }

};


#endif
