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

/** structure pour ex interpret **/
typedef struct {

	myValueKeyList recorder;		/** liste d'enregistrement **/
	myValueKeyList trash;			/** liste poubelle **/
	myValueKeyList* current;

} myExInterpret;

typedef bool(*interpret)(void*, myExInterpret*);

extern myExInterpret createExInterpret(void*, interpret);
extern bool insertIntoCurrentList(wchar_t* s, myExInterpret* l);
extern bool expression_cmp(void*, myString, myExInterpret*);
extern bool expression_size(void*, int, myExInterpret*);
extern bool expression_ident(void*, wchar_t, wchar_t, myExInterpret*);
extern bool expression_notin(void*, wchar_t*, unsigned int, myExInterpret*);
extern bool expression_in(void*, wchar_t*, unsigned int, myExInterpret*);
extern bool expression_loop_notin(void*, wchar_t*, unsigned int, myExInterpret*);
extern bool expression_loop_in(void*, wchar_t*, unsigned int, myExInterpret*);
extern bool type(void*, interpret, myString, myExInterpret*);
extern bool or(void*, interpret, interpret, myExInterpret*);
extern bool and(void*, interpret, interpret, myExInterpret*);
extern bool loop(void*, myString, interpret, interpret, myString, myString, myExInterpret*);
extern bool surround(void*, myString, interpret, myString, myExInterpret*);
extern bool activateTrashList(myExInterpret* l);
extern bool activateRecordList(myExInterpret* l);
extern bool contextChange(void*, int newContext);


#endif /* exInterpret_h */
