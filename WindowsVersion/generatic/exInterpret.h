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

typedef bool(*interpret)(void*, myValueKeyList*);
extern myValueKeyList createExInterpret(void*, interpret);
extern bool expression_cmp(void*, myString, myValueKeyList*);
bool expression_size(void*, int, myValueKeyList*);
bool expression_ident(void*, wchar_t, wchar_t, myValueKeyList*);
bool expression_notin(void*, wchar_t*, unsigned int, myValueKeyList*);
bool expression_in(void*, wchar_t*, unsigned int, myValueKeyList*);
bool type(void*, interpret, myString, myValueKeyList*);
bool or(void*, interpret, interpret, myValueKeyList*);
bool and(void*, interpret, interpret, myValueKeyList*);
bool loop(void*, myString, interpret, myString, myString, myValueKeyList*);
bool surround(void*, myString, interpret, myString, myValueKeyList*);
bool contextChange(void*, int newContext);


#endif /* exInterpret_h */
