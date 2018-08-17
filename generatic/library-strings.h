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


#ifndef library_strings_h
#define library_strings_h

#define MINSIZE     255


/**
 **   Represents a variable-length list of chars
 **/
typedef struct {
    
    wchar_t* strContent;        /** pointer of data, ends with '\0' **/
    unsigned int  used;         /** number of chars, used + 1 == capacity **/
    unsigned int  capacity;     /** maximum of buffer size in byte **/
    
} myString;

/**
 **   Associe un couple nom/valeur
 **/
typedef struct {
    
    myString question;
    myString name;
    myString value;
    
} myKey;

/**
 **   Represents a variable-length list of keys
 **/
typedef struct {
    
    myKey* list;                /** list of data, ends with '\0' **/
    unsigned int used;          /** number of elements, used + 1 == capacity **/
    unsigned int capacity;      /** size of elements * one element = capacity **/
    
} myList;


extern wchar_t nonDosFormat(FILE*);
extern myList createList(unsigned int);
extern myKey createKey(void);
extern myString createString(unsigned int);
extern void freeString(myString*);
extern void freeKey(myKey*);
extern void freeList(myList*);
extern int compareString(myString, myString);
extern myString* writeString(myString*, wchar_t*);
extern myList* writeList(myList*, wchar_t*, wchar_t*, wchar_t*);
extern wchar_t* search(myList*, wchar_t*);
extern void eraseFile(char*);
typedef bool (*writeLine)(myString*);
extern void writeFile(char*, writeLine);

#endif /* library_strings_h */
