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


#ifndef cmd_h
#define cmd_h

extern bool searchCommandName(myCommand*, myCommandList*);
extern bool searchCommandOption(myCommand*, myCommandList*, myCommandList*);

#endif /* cmd_h */
