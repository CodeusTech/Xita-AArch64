%{
/*
  xcsl.l (AArch64)
  Cody Fagley
  Authored on   January 30, 2019
  Last Modified    July 24, 2019
*/

/*
  Contains lexical tokens for use in XCS grammar

  Table of Contents
  =================
  1.) Comments
  2.) Primitive Types/Constructors
  3.) Override Operators
  4.) Syntactic Operators
  5.) Conditional Keywords
  6.) Functional Keywords
  7.) Datatype Keywords
  8.) Filesystem Operations
  9.) Special Operations

  A.) Tether Modules 
  B.) Constructors/Identifiers
*/

#include "xcsl.tab.c"
extern int yylex();

#include "string.h"

%}
%option noyywrap
%option yylineno
%x COMMENT
%x DOC_COMMENT
%x STR
%x CHR
%%
[ \t\n] ;           // Eliminate Whitespace


"!SOURCE\n" { return SOURCE_H; }  // SOURCE PREAMBLE
"!HEADER\n" { return HEADER_H; }  // HEADER PREAMBLE
"!TETHER\n" { return TETHER_H; }  // TETHER PREAMBLE


%{
/*
  1.) Comments
*/
%}

"(!*" { 
  BEGIN(DOC_COMMENT); 
  yylval.val_doc = (char*) malloc(4096);  //  Max 4096 Characters per Reference Guide
  yylval.val_doc[0] = '\0';
}
<DOC_COMMENT>"*)"        { BEGIN(INITIAL); return DOC; }
<DOC_COMMENT>"*"+[^*)]*  { strncat(yylval.val_doc, yytext, strlen(yytext)); }
<DOC_COMMENT>[^*]*       { strncat(yylval.val_doc, yytext, strlen(yytext)); }

"!ref" { return REFERENCE; } // For Use with Doc Comments

"(*"                 BEGIN(COMMENT);
<COMMENT>"*)"        BEGIN(INITIAL);
<COMMENT>"*"+[^*)]*  { }
<COMMENT>[^*]*       { }

--[^\n]*\n { }

%{
/*
  2.) Primitive Types/Constructors
*/
%}


"int" { return INT_T;  }  //  INFERRED INTEGER TYPE
"u8" { return U8_T; }     //  8-Bit UNSIGNED INTEGER TYPE
"i8" { return I8_T; }     //  8-Bit SIGNED INTEGER TYPE
"u16" { return U16_T; }   //  16-Bit UNSIGNED INTEGER TYPE
"i16" { return I16_T; }   //  16-Bit SIGNED INTEGER TYPE
"u32" { return U32_T; }   //  32-Bit UNSIGNED INTEGER TYPE
"i32" { return I32_T; }   //  32-Bit SIGNED INTEGER TYPE
"u64" { return U64_T; }   //  64-Bit UNSIGNED INTEGER TYPE
"i64" { return I64_T; }   //  64-Bit SIGNED INTEGER TYPE

"rng" { return RNG; } //  RANDOM NUMBER GENERATOR

"bool" { return BOOL_T; }   //  BOOLEAN TYPE
"True" { return TRUE; }     //  BOOLEAN PRIMITIVE
"False" { return FALSE; }   //  BOOLEAN PRIMITIVE

"real" { return REAL_T; }       //  INFERRED REAL NUMBER TYPE
"float" { return FLOAT_T; }     //  FLOATING POINT TYPE
"Float" { return FLOAT_C; }     //  FLOATING POINT CONSTRUCTOR
"double" { return DOUBLE_T; }   //  DOUBLE PRECISION TYPE
"Double" { return DOUBLE_C; }   //  DOUBLE PRECISION CONSTRUCTOR

"char" { return CHAR_T; }  //  CHARACTER TYPE
"Char" { return CHAR_C; }  //  CHARACTER CONSTRUCTOR 
"string" { return STRING_T; }  //  STRING TYPE
"String" { return STRING_C; }  //  STRING CONSTRUCTOR

"list" { return LIST_T; } //  LIST TYPE
"List" { return LIST_C; } //  LIST CONSTRUCTOR


%{
/*
  3.) Override Operators
*/
%}


"(&&)" { return BOOL_AND_O; } // BOOLEAN AND
"(||)" { return BOOL_OR_O;  } // BOOLEAN OR
"(^^)" { return BOOL_XOR_O; } // BOOLEAN XOR

"(<<)" { return BIT_SHL_O; } // BITWISE SHIFT LEFT
"(>>)" { return BIT_SHR_O; } // BITWISE SHIFT RIGHT
"(&)"  { return BIT_AND_O; } // BITWISE AND
"(|)"  { return BIT_OR_O;  } // BITWISE OR
"(^)"  { return BIT_XOR_O; } // BITWISE XOR

"(*->)"   { return MEM_READ_O; }  //  READ FROM MEMORY
"(<-*)"   { return MEM_SET_O; }   //  SET MEMORY

"(<-)"    { return ARROW_L_O; }   //  LEFT FACING ARROW
"(->)"    { return ARROW_R_O; }   //  RIGHT FACING ARROW

"(++)" { return OP_APPEND_O; }   //  APPEND LISTS
"(:)"  { return OP_LIST_CON_O; } //  CONSTRUCT LISTS

"(+)" { return OP_ADD_O; } //  ADDITION OPERATOR
"(-)" { return OP_SUB_O; } //  SUBTRACTION OPERATOR  
"(*)" { return OP_MUL_O; } //  MULTIPLICATION OPERATOR
"(/)" { return OP_DIV_O; } //  DIVISION OPERATOR
"(%)" { return OP_MOD_O; } //  MODULUS OPERATOR

"(<=)" { return OP_LTE_O; } // LESS THAN OR EQUAL TO
"(>=)" { return OP_GTE_O; } // GREATER THAN OR EQUAL TO
"(==)" { return OP_EQ_O;  } // EXACTLY EQUAL TO
"(!=)" { return OP_NEQ_O; } // NOT EQUAL TO
"(<)"  { return OP_LT_O;  } // LESS THAN
"(>)"  { return OP_GT_O;  } // GREATER THAN


%{
/*
  4.) Syntactic Operators
*/
%}

"&&" { return BOOL_AND; } // BOOLEAN AND
"||" { return BOOL_OR;  } // BOOLEAN OR
"^^" { return BOOL_XOR; } // BOOLEAN XOR

"<<" { return BIT_SHL; } // BITWISE SHIFT LEFT
">>" { return BIT_SHR; } // BITWISE SHIFT RIGHT
"&"  { return BIT_AND; } // BITWISE AND
"|"  { return BIT_OR;  } // BITWISE OR
"^"  { return BIT_XOR; } // BITWISE XOR

"*->"   { return MEM_READ; }  //  READ FROM MEMORY
"<-*"   { return MEM_SET; }   //  SET MEMORY

"<-"    { return ARROW_L; }   //  LEFT FACING ARROW
"->"    { return ARROW_R; }   //  RIGHT FACING ARROW

"++" { return OP_APPEND; }   //  APPEND LISTS
":"  { return OP_LIST_CON; } //  CONSTRUCT LISTS
"hd" { return LIST_HEAD; }   //  HEAD OF LIST
"tl" { return LIST_TAIL; }   //  TAIL OF LIST

"+" { return OP_ADD; } //  ADDITION OPERATOR
"-" { return OP_SUB; } //  SUBTRACTION OPERATOR  
"*" { return OP_MUL; } //  MULTIPLICATION OPERATOR
"/" { return OP_DIV; } //  DIVISION OPERATOR
"%" { return OP_MOD; } //  MODULUS OPERATOR

":=" { return OP_INLINE; } //  INLINE OPERATOR

"<=" { return OP_LTE; } // LESS THAN OR EQUAL TO
">=" { return OP_GTE; } // GREATER THAN OR EQUAL TO
"==" { return OP_EQ;  } // EXACTLY EQUAL TO
"!=" { return OP_NEQ; } // NOT EQUAL TO
"<"  { return OP_LT;  } // LESS THAN
">"  { return OP_GT;  } // GREATER THAN

"(" { return PAR_LEFT; }  //  LEFT PARENTHESIS
")" { return PAR_RIGHT; } //  RIGHT PARENTHESIS

"="  { return OP_ASSIGN; } //  ASSIGNMENT OPERATOR
";;" { return OP_SEP; }    //  SEPERATOR OPERATOR
";"  { return OP_TUP; }    //  TUPPLE OPERATOR
","  { return OP_COMMA; }  //  COMMA OPERATOR
"."   { return OP_ELEMENT; } //  ACCESS ELEMENT OPERATOR

"["  { return OP_LIST_L; }  //  BEGINNING OF LIST
"]"  { return OP_LIST_R; }  //  END OF LIST

"{"  { return OP_REC_L; }
"}"  { return OP_REC_R; }

%{
/*
  5.) Conditional Keywords
*/
%}

"if"    {return IF; }
"then"  {return THEN; }
"else"  {return ELSE; }

"match" {return MATCH; }
"with"  {return WITH;  }

%{
/*
  6.) Functional Keywords
*/
%}

"const" { return CONST; }

"let" { return LET; }
"in"  { return IN;  }


%{
/*
  7.) Datatype Keywords
*/  
%}

"type"       { return TYPE;      }
"typeclass"  { return TYPECLASS; }

"is"        { return IS;  }
"of"        { return OF;  }
"requires"  { return REQ; }
"implements" { return IMPL;  }

"this"      { return THIS; }


%{
/*
  8.) Filesystem Operations
*/
%}

"file"    { return FILEK;  }
"remove"  { return REMOVE; }

"read"    { return READ;   }
"write"   { return WRITE;  }
"append"  { return APPEND; }

"search"  { return SEARCH; }
"tsearch" { return TSEARCH;}

"copy"    { return COPY;   }
"move"    { return MOVE;   }
"retag"   { return RETAG;  }


%{
/*
  9.) Special Operations
*/  
%}

"build"   { return BUILD; }
"run"     { return RUN;   }
"tether"  { return TETHER;}

"send"    { return SEND;    }
"receive" { return RECEIVE; }

"regex"   { return REGEX; }

"open"    { return OPEN; }
"Tether"  { return TETHER_M; }
"Source"  { return SOURCE_M; }
"Header"  { return HEADER_M; }

%{
/*
  A.) Tether Modules
*/  
%}

"offer"   { return OFFER;   }
"request" { return REQUEST; }

%{
/*
  B.) Miscellanous Utilities
*/  
%}

"clear"  {return CLEAR;}
"sizeof" {return SIZEOF;}
"delay"  {return DELAY; }




%{
/*
  C.) Constructors/Identifiers
*/
%}

0[bB][01]+           { yylval.val_int = strtol(yytext, NULL,  2); return INT; } //  BINARY PRIMITIVE
0[oO][0-7]+          { yylval.val_int = strtol(yytext, NULL,  8); return INT; } //  OCTAL PRIMITIVE
0[xX][0-9a-fA-F]+    { yylval.val_int = strtol(yytext, NULL, 16); return INT; } //  HEXADECIMAL PRIMITIVE

[0-9]+            { yylval.val_int = atoll(yytext); return INT; }    //  INTEGER PRIMITIVE
[0-9]+\.[0-9]*    { yylval.val_real = atof(yytext); return REAL; }  //  REAL PRIMITIVE

\"              BEGIN(STR);
<STR>([^"])* { yylval.val_string = strdup(yytext); return STRING; }  //  STRING PRIMITIVE
<STR>\"         BEGIN(INITIAL);

'              BEGIN(CHR);
<CHR>([^']){0,2}  { yylval.val_char = get_char_code(yytext); return CHAR; }  //  CHARACTER PRIMITIVE
<CHR>'         BEGIN(INITIAL);

[A-Z][a-zA-Z0-9_]*\'?   { yylval.val_ident = strdup(yytext); return CONSTRUCTOR; }
[a-z_][a-zA-Z0-9_]*\'?  { yylval.val_ident = strdup(yytext); return IDENTIFIER;  }