//
//  library-strings.h
//  generatic
//
//  Created by Olivier on 15/08/2018.
//  Copyright © 2018 Olivier. All rights reserved.
//

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
extern myString createData(unsigned int);
extern void freeData(myString*);
extern void freeKey(myKey*);
extern void freeList(myList*);
extern int compareData(myString, myString);
extern myString* writeData(myString*, wchar_t*);
extern myList* writeList(myList*, wchar_t*, wchar_t*, wchar_t*);
extern wchar_t* search(myList*, wchar_t*);
extern void eraseFile(char*);
typedef bool (*writeLine)(myString*);
extern void writeFile(char*, writeLine);

#endif /* library_strings_h */
