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

typedef bool(*interpret)(myString, unsigned int, myValueKeyList*);
extern myValueKeyList createExInterpret(myString, interpret);
extern bool expression(myString, unsigned int, myString, myValueKeyList*);
bool expression(myString, unsigned int, int, myValueKeyList*);
bool expression(myString, unsigned int, wchar_t, wchar_t, myValueKeyList*);
bool type(myString, unsigned int, interpret, myString, myValueKeyList*);
bool or(myString, unsigned int, interpret, interpret, myValueKeyList*);
bool loop(myString, unsigned int, myString, interpret, myString, myString, myValueKeyList*);
bool surround(myString, unsigned int, myString, interpret, myString, myValueKeyList*);


#endif /* exInterpret_h */
