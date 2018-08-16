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
 **   Hack to do not read
 **   \r
 **
 **/
bool nonDosFormatString(myString s, wchar_t* c, int* index) {
    
    if (*index < s.used) {
        *c = s.strContent[*index];
        ++(*index);
        if (*c == L'\r') {
            return nonDosFormatString(s, c, index);
        }
        else
            return true;
    }
    else
        return false;
    
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
        
        if (c == L' ' || c == L'\t' || c == L',') {
            
            if (!afterSpace) {
                
                if (state == 0) {
                    
                    writeString(&result->name, value.strContent);
                    memset(value.strContent, 0, value.used);
                    value.used = 0;
                    state = 1;
                    afterSpace = true;

                } else if (state == 1) {
                    
                    writeString(&result->option, value.strContent);
                    memset(value.strContent, 0, value.used);
                    value.used = 0;
                    state = 2;
                    afterSpace = true;

                } else {
                    
                    myCommand cmd = createCommand();
                    writeString(&cmd.name, value.strContent);
                    writeCommand(&result->parameters, &cmd);
                    memset(value.strContent, 0, value.used);
                    value.used = 0;
                    afterSpace = true;

                }

            }
            
        } else {
            
            afterSpace = false;
            input[0] = c;
            writeString(&value, input);
            
        }
        
    }
    
    if (value.used > 0) {
        
        if (state == 0) {
            
            writeString(&result->name, value.strContent);
            memset(value.strContent, 0, value.used);
            value.used = 0;
            state = 1;
            afterSpace = true;
            
        } else if (state == 1) {
            
            writeString(&result->option, value.strContent);
            memset(value.strContent, 0, value.used);
            value.used = 0;
            state = 2;
            afterSpace = true;
            
        } else {
            
            myCommand cmd = createCommand();
            writeString(&cmd.name, value.strContent);
            writeCommand(&result->parameters, &cmd);
            memset(value.strContent, 0, value.used);
            value.used = 0;
            afterSpace = true;
            
        }

    }
    
    freeString(&value);
    
    if (state > 0) {
        
        fwprintf(stdout, L"%ls %ls ", result->name.strContent, result->option.strContent);
        for(int index = 0; index < result->parameters.used; ++index) {
            
            myCommand* c = (myCommand*)result->parameters.element;
            fwprintf(stdout, L"%ls ", c[index].name.strContent);
            
        }
        fflush(stdout);
        return true;

    } else {
        
        return false;
        
    }
    
}
