//
//  fileSystem.c
//  generatic
//
//  Created by Olivier on 17/08/2018.
//  Copyright © 2018 Olivier. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdbool.h>
#include <assert.h>
#include "fileSystem.h"


/**
 **  Function to create one directory
 **/
void createOneDirectory(wchar_t* dir) {
    
    char cmd[256] = "./createDirectory.sh '";
    strcat(cmd, (char*)dir);
    strcat(cmd, "'");
    system(cmd);
}

void createAllDirectory(wchar_t* dir) {
    
    
    
}
