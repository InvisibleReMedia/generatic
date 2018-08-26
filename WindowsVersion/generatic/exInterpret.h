/**
**
**   Langage C
**   Projet Generatic
**   17/7/18 CET 10:00
**   business.forward.technology@gmail.com
**   Ce source peut être compilé avec:
**     - XCode (MacOS)
**     - Code::Blocks et GNU GCC
**
**/

#ifndef exInterpret_h
#define exInterpret_h

typedef bool(*interpret)(myYieldReadPart*, myValueKeyList*);
extern myValueKeyList createExInterpret(myYieldReadPart*, interpret);
extern bool expression_cmp(myYieldReadPart*, myString, myValueKeyList*);
bool expression_size(myYieldReadPart*, int, myValueKeyList*);
bool expression_ident(myYieldReadPart*, wchar_t, wchar_t, myValueKeyList*);
bool type(myYieldReadPart*, interpret, myString, myValueKeyList*);
bool or(myYieldReadPart*, interpret, interpret, myValueKeyList*);
bool loop(myYieldReadPart*, myString, interpret, myString, myString, myValueKeyList*);
bool surround(myYieldReadPart*, myString, interpret, myString, myValueKeyList*);


#endif /* exInterpret_h */
