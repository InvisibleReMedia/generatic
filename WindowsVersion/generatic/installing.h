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

extern myCSV  languages;
extern myCSV* languagesCommand;

extern myCommandList install(void);
extern myModel initialize(void);
extern void installLanguages(void);
extern myCSV installLanguageCommands(myModel*, myString);
extern bool searchLanguageName(wchar_t*, myString*);

#endif /* installing_h */
