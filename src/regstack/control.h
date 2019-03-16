/*
  control.h
  Cody Fagley
  Authored on   March 14, 2019
  Last Modified March 14, 2019
*/

/*
  Contains Control/Status Operations for Managing the Register Stack

  Table of Contents
  =================
  1.) Initialize Register Stack
  2.) Finalize Register Stack
*/

#ifndef REGSTACK_CONTROL_H
#define REGSTACK_CONTROL_H

extern ADR** rs;  //  Global Register Stack Orders
extern Scope scope_next;
extern unsigned int** rs_types;
extern unsigned int rse_next;
extern unsigned long** rse_types;


/* 1.) Initialize Register Stack

  Returns:
    0, if Successful
*/
int rs_init()
{
  printf("rs_init() Called...\n");
  //   Initialize Register Stack Buffers, and 1st Reg Stack
  rs = (ADR**) malloc(4096 * sizeof(ADR*));
  rs[0] = (ADR*) malloc(31 * sizeof(ADR));
  rs[0][31] = NULL;  // Indicates Extended Space isn't used

  //  Initialize Register Stack Types Buffer
  rs_types = (unsigned int**) malloc(4096 * sizeof(unsigned int*));
  rs_types[0] = (unsigned int*) malloc(30 * sizeof(unsigned int));

  //  Initialize Register Stack Types Buffer (Extended)
  rse_types = (unsigned long**) malloc(4096 * sizeof(unsigned long*));
  rse_types[0] = NULL;  //  RESERVED

  return 0;
}


/* 2.) Finalize Register Stack

  Returns:
    0, if Successful
*/
int rs_end()
{
  printf("rs_finish() Called...\n");
  for (int i = 0; i < scope_next; i++)
  {
    if (rs[i][31] == NULL) 
    {
      free(rs[i]);
      free(rs_types[i]);
    }
    //  Else Free Extended Space As Well
    else 
    {
      free (rs[i]);
      free (rs_types[i]);
    }
  }

  for (int i = 1; i < rse_next; i++)
  {
    free(rse_types[i]);
  }

  free(rs);
  free(rs_types);
  free(rse_types);

  printf("Check 2\n");

  return 0;
}

#endif