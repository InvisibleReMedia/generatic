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
#include "csv-reader.h"
#include "installing.h"
#include "parse-cmd.h"
#include "cmd.h"


/**
 **  Search command from available commands
 **
 **/
bool searchCommandName(myCommand* src, myCommandList* results) {
    
    /** recherche de toutes les commandes du même nom **/
    myCommandList selected = createCommandList(0);
    myCommand* c = (myCommand*)builtInCommands.element;
    for(int index = 0; index < builtInCommands.used; ++index) {
        
        if (wcscmp(src->name.strContent, c[index].name.strContent) == 0) {
            
            writeCommand(&selected, &c[index]);
            
        }
        
    }
    c = (myCommand*)model.currentSession->specifics.element;
    for(int index = 0; index < model.currentSession->specifics.used; ++index) {
        
        if (wcscmp(src->name.strContent, c[index].name.strContent) == 0) {
            
            writeCommand(&selected, &c[index]);
            
        }
        
    }

    *results = selected;
    if (selected.used > 0)
        return true;
    else
        return false;
    
}


bool searchCommandOption(myCommand* src, myCommandList* selected, myCommandList* results) {
    
    /** recherche de toutes les options du même nom **/
    myCommandList optional = createCommandList(0);
    myCommand* c = (myCommand*)selected->element;
    for(int index = 0; index < selected->used; ++index) {
        
        if (wcscmp(src->option.strContent, c[index].option.strContent) == 0) {
            
            writeCommand(&optional, &c[index]);
            
        }
        
    }
    
    *results = optional;
    if (optional.used > 0)
        return true;
    else
        return false;
    
}

