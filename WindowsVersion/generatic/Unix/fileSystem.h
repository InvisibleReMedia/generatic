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

#ifndef fileSystem_h
#define fileSystem_h

extern void createDirectory(wchar_t*, wchar_t*);
extern void createFile(wchar_t*, wchar_t*);
extern void deleteFile(wchar_t*, wchar_t*);
extern void deleteDirectory(wchar_t*,wchar_t*);
extern void printFile(wchar_t*,wchar_t*);
extern void eraseFile(char*);
typedef bool (*writePart)(myString*);
typedef bool (*readPart)(myString*, void*, void*);

typedef struct {
    
    FILE*          file;
    myString       line;
    unsigned int   pos;
    
} myYieldReadPart;
typedef bool (*yieldReadPart)(myYieldReadPart*, void*, void*);

extern void writeFile(char*, writePart);
extern void readFromFile(char*, readPart, void*, void*);
extern void yieldReadFromFile(char*, yieldReadPart, void*, void*);
extern bool yieldnReadInMemory(myYieldReadPart*, unsigned int);
extern bool yieldnRead(myYieldReadPart*, unsigned int, bool);
extern bool yieldnReadOut(myYieldReadPart*, unsigned int);
extern bool yieldRead(myYieldReadPart*);

#endif /* fileSystem_h */
