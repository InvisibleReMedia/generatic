//
//  dataModel.h
//  generatic
//
//  Created by Olivier on 16/08/2018.
//  Copyright © 2018 Olivier. All rights reserved.
//

#ifndef dataModel_h
#define dataModel_h


/**
 ** A couple of name/value
 **/
typedef struct {
    
    myString name;          /** name of key **/
    myString value;         /** content of this key **/
    
} myValueKey;

/**
 **  List of key and value
 **/
typedef struct {
    
    myValueKey*   element;         /** one couple **/
    unsigned int  used;         /** number of chars, used + 1 == capacity **/
    unsigned int  capacity;     /** maximum of buffer size in byte **/

} myValueKeyList;

/**
 **  a pointer to a command structure
 **/
typedef void* myPtrCommand;

/**
 **  List of commands
 **/
typedef struct {
    
    myPtrCommand  element;       /** command **/
    unsigned int  used;         /** number of chars, used + 1 == capacity **/
    unsigned int  capacity;     /** maximum of buffer size in byte **/

} myCommandList;

/**
 **  Command
 **/
typedef struct {
    
    myString name;               /** command name **/
    myString option;             /** command option **/
    myCommandList parameters;    /** parameters **/

} myCommand;

/**
 **  Indent
 **/
typedef struct {
    
    unsigned int* lineNumbers;  /** list of line number **/
    unsigned int  used;         /** number of chars, used + 1 == capacity **/
    unsigned int  capacity;     /** maximum of buffer size in byte **/
    
} myTabList;

/**
 **  Session
 **/
typedef struct {
    
    struct {
        
        myString path;          /** path of project **/
        myString name;          /** project name **/
        
    } currentProject;           /** current project **/
    
    struct {
        
        myString path;          /** path of file **/
        myString name;          /** file name **/

    } currentFile;              /** current file **/

    myString language;          /** current language **/
    
    
    myCommandList commands;         /** command list **/
    
} mySession;

/**
 **  Session list
 **/
typedef struct {
    
    mySession* sx;              /** session pointer **/
    unsigned int  used;         /** number of chars, used + 1 == capacity **/
    unsigned int  capacity;     /** maximum of buffer size in byte **/
    
} mySessionList;

typedef struct {
    
    myValueKeyList config;          /** configurations **/
    mySessionList  sessions;        /** sessions */
    
} myProject;


extern myValueKeyList createValueKeyList(unsigned int);
extern myCommandList createCommandList(unsigned int);
extern myTabList createTabList(unsigned int);
extern mySessionList createSessionList(unsigned int);
extern void freeValueKey(myValueKey*);
extern void freeCommand(myCommand*);
extern void freeSession(mySession*);
extern void freeValueKeyList(myValueKeyList*);
extern void freeCommandList(myCommandList*);
extern myValueKeyList* removeAtValueKeyList(myValueKeyList*, unsigned int);
extern myCommandList* removeAtCommandList(myCommandList*, unsigned int);
extern myTabList* removeAtTabList(myTabList*, unsigned int);
extern mySessionList* removeAtSessionList(mySessionList*, unsigned int);
extern myValueKey createValueKey(void);
extern myCommand createCommand(void);
extern mySession createSession(void);



#endif /* dataModel_h */
