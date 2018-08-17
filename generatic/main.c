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
#include "installing.h"
#include "parse-cmd.h"
#include "cmd.h"


/** Elements globaux (constants) **/
myCommandList builtInCommands;
myModel model;


/**
 **   Attend la saisie au clavier
 **/
void entry() {
    
    myString line;
    wchar_t input[2];
    
    line = createString(MINSIZE);
    
    input[1] = '\0';
    bool finished = false;
    
    do {
        
        printf(">>> ");
        memset(line.strContent, 0, line.used);
        line.used = 0;
        /** vide le flux **/
        fflush(stdin);
        input[0] = '\0';
        do {
            
            writeString(&line, input);
            input[0] = nonDosFormat(stdin);
            // parsing automatique

            if (input[0] == '\n') {
                writeString(&line, input);
                
                myCommand o = createCommand();
                if (parseCommand(line, &o)) {
                    
                    if (searchCommand(&o, &builtInCommands)) {
                        
                        wprintf(L"    OK\n");
                        
                        (*o.execCommand)(&model, &o);

                    }
                }
                
                
                if (wcsncmp(line.strContent, L"quit\n", 5) == 0) {
                    finished = true;
                }
            }

        } while(input[0] != '\n' && input[0] != '\xff' && input[0] != '\0');
        
        
        
    } while (!finished);
    
    freeString(&line);
    
}




int main(int argc, const char * argv[]) {

    builtInCommands = install();
    model = initialize();
    printf("generatic copyright @ 2018\n");
    printf("Automatic programming hobbie\n");
    printf("See help\n");
    
    entry();
    
    freeCommandList(&builtInCommands);
    freeModel(&model);
    
    return 0;
}

