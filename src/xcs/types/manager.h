/*
  manager.h (Type Manager)
  Codeus Tech
  Authored on   June 1, 2020
  Last Modified July 1, 2021
*/

/*
  Contains structures/definitions for Xita Type Manager

  The TypeManager provides a central interface for dynamic type-checking
  expressions of arbitrary structure in Xita.  Additionally, Xita offers
  dynamic Constructor checking when possible to allow faster development.

  NOTE: This will be used eventually, but it is NOT used right now.  
  TODO: This needs to be integrated into ContextManager and relinked
        through entire system when type-checking is necessary.
*/

#pragma once

#include <vector>

#include <xcs/std/includes.h>
#include "types.h"

using namespace std;


class TypeManager
{
  /*
    Private Data
  */

protected:
  /*
    Protected Data
  */
  ModuleID context;

  //  Buffered Data
  vector<TypeNode> types;
  vector<TypeConstructor> constructors;

  //  Active data
  vector<TypeID> activeTypes;
  vector<ConstructorID> activeConstructors;

public: 
  TypeManager(ModuleID _context);

  ErrorCode declareType(TypeID tid, Identifier ident);
  ErrorCode declareType(TypeID tid, Identifier ident, unsigned long size);
  ErrorCode declareConstructor(ConstructorID cid, Identifier ident);
  ErrorCode declareParameter(TypeID tid, Identifier ident);

  TypeID getTypeID(Identifier ident);
  TypeID getTypeID(ConstructorID cid);

  Identifier getIdentifier() { return types.back().Ident(); }
  Identifier getIdentifier(Index i) { return types[i].Ident(); }
};
