//
//  main.c
//  generatic
//
//  Created by Olivier on 15/08/2018.
//  Copyright © 2018 Olivier. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdbool.h>
#include <assert.h>
#include "library-strings.h"
#include "dataModel.h"


/**
 **   Attend la saisie au clavier
 **/
void entry() {
    
    myString line;
    wchar_t input[2];
    
    line = createData(MINSIZE);
    
    input[1] = '\0';
    bool finished = false;
    
    do {
        
        printf(">>> ");
        memset(line.strContent, 0, line.used);
        line.used = 0;
        input[0] = '\0';
        do {
            
            writeData(&line, input);
            input[0] = nonDosFormat(stdin);
            // parsing automatique

            if (input[0] == '\n') {
                writeData(&line, input);
                wprintf(line.strContent);
                if (wcsncmp(line.strContent, L"quit\n", 5) == 0) {
                    finished = true;
                }
            }

        } while(input[0] != '\n' && input[0] != '\xff' && input[0] != '\0');
        
        
        
    } while (!finished);
    
    freeData(&line);
    
}


int main(int argc, const char * argv[]) {

    printf("generatic copyright @ 2018\n");
    printf("Automatic programming hobbie\n");
    printf("See help\n");
    
    entry();
    
    return 0;
}

