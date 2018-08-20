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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdbool.h>
#include <assert.h>
#include "library-strings.h"
#include "dataModel.h"
#include "parse-cmd.h"

/**
 **  Write string and empty src, udpate state and afterSpace
 **
 **/
void writeName(myString* name, myString* src, int* state, bool* afterSpace) {
    
    writeString(name, src->strContent);
    memset(src->strContent, 0, src->used);
    src->used = 0;
    *state = 1;
    *afterSpace = true;
    
}

/**
 **  Write option and empty src, udpate state and afterSpace
 **
 **/
void writeOption(myString* option, myString* src, int* state, bool* afterSpace) {
    
    writeString(option, src->strContent);
    memset(src->strContent, 0, src->used);
    src->used = 0;
    *state = 2;
    *afterSpace = true;
    
}

/**
 **  Write parameter into command and empty src, udpate state and afterSpace
 **
 **/
void writeParameter(myCommand* result, myString* src, int* state, bool* afterSpace) {
    
    myCommand cmd = createCommand();
    writeString(&cmd.value, src->strContent);
    writeCommand(&result->parameters, &cmd);
    memset(src->strContent, 0, src->used);
    src->used = 0;
    *afterSpace = true;

}


/**
 **  Parse a command
 **/
bool parseCommand(myString s, myCommand* result) {
        
    wchar_t input[2];
    input[1] = L'\0';
    int pos = 0;
    wchar_t c;
    int state = 0;
    bool afterSpace = true;
    myString value = createString(MINSIZE);

    while(nonDosFormatString(s, &c, &pos)) {
        
        if (c == L'\n' || ((c == L' ' || c == L'\t') && state >= 0) || (c == L',' && state > 1)) {
            
            if (!afterSpace) {
                
                if (state == 0) {
                    
                    writeName(&result->name, &value, &state, &afterSpace);

                } else if (state == 1) {
                    
                    writeOption(&result->option, &value, &state, &afterSpace);

                } else {

                    /** recherche de commande dans le fichier csv **/
                    writeParameter(result, &value, &state, &afterSpace);

                }

            }
            
        } else {
            
            afterSpace = false;
            input[0] = c;
            writeString(&value, input);
            
        }
        
    }
    
    /** possible ? **/
    if (value.used > 0) {
        
        if (state == 0) {
            
            writeName(&result->name, &value, &state, &afterSpace);
            
        } else if (state == 1) {
            
            writeOption(&result->option, &value, &state, &afterSpace);
            
        } else {
            
            writeParameter(result, &value, &state, &afterSpace);
            
        }

    }
    
    freeString(&value);
    
    return state > 0;
}
