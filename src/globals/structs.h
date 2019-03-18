/*
  structs.h
  Cody Fagley
  Authored on   March 8, 2019
  Last Modified March 8, 2019
*/

/*
  Contains data structure definitions for use in global buffers

  Table of Contents
  =================
  1.) Infrastructure
    1.a) Assembly Infrastructure
  2.) Register Stacks
  3.) Functions
  4.) Data Types
  6.) Memory Allocator Structures
  7.) Operator Structures
    7.a) Operand Pairs
*/

#ifndef GLOBALS_STRUCTS_H
#define GLOBALS_STRUCTS_H

/*
  1.) Infrastructure
*/

typedef int ErrorCode;

typedef char* Identifier;
typedef char* Constructor;

/*
  1.a) Assmebly Infrastructure
*/

typedef char* Command;

/*
  2.) Register Stacks
*/

typedef unsigned char ADR;
typedef unsigned int Scope;

typedef struct regstack_t
{
  ADR order[30];
} RegStack;


/*
  3.) Functions
*/

typedef unsigned long ConstantID;
typedef unsigned long FunctionID;


/*
  4.) Data Types
*/

//  4.a) Types
typedef unsigned long TypeID;

//  4.b) Typeclasses
typedef unsigned long TypeclassID;
typedef unsigned int PrototypeID;

/*
  6.) Memory Allocator Structures
*/


typedef struct mem_block
{
  struct mem_block* left;
  struct mem_block* right;
  unsigned int height;
  unsigned long addr;
  unsigned long size;
  void* data;
} MemoryBlock;

MemoryBlock* ActiveMemory;



/*
  7.) Operator Structures
*/

/*
  7.a) Operand Pairs
*/
typedef struct operands_t
{
  unsigned int lhs; // Left-Hand Side  Type Code
  unsigned int rhs; // Right-Hand Side Type Code
} operands;

#endif
