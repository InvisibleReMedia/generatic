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


#ifndef installing_h
#define installing_h

extern myCSV languages;
extern myCommandList builtInCommands;
extern myModel model;

extern void install(void);
extern void initialize(void);
extern void installLanguages(void);
extern void installLanguageCommands(myModel*, myString);
extern bool searchLanguageName(wchar_t*, myString*);

#endif /* installing_h */
