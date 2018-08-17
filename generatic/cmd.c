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
#include "cmd.h"


/**
 **  Search command from builtin commands
 **
 **/
bool searchCommand(myCommand* src, myCommandList* builtin) {
    
    /** recherche de toutes les commandes du même nom **/
    myCommandList selected = createCommandList(0);
    myCommand* c = (myCommand*)builtin->element;
    for(int index = 0; index < builtin->used; ++index) {
        
        if (wcscmp(src->name.strContent, c[index].name.strContent) == 0) {
            
            writeCommand(&selected, &c[index]);
            
        }
        
    }
    
    /** recherche de toutes les options du même nom **/
    if (selected.used > 0) {
        
        myCommandList optional = createCommandList(selected.used);
        myCommand* c = (myCommand*)selected.element;
        for(int index = 0; index < selected.used; ++index) {
            
            if (wcscmp(src->option.strContent, c[index].option.strContent) == 0) {
                
                writeCommand(&optional, &c[index]);
                
            }
            
        }
        
        /** s'il ne reste qu'une seule commande possible **/
        if (optional.used == 1) {
            
            myCommand* d = (myCommand*)optional.element;
            myCommand* opar = (myCommand*)d->parameters.element;
            myCommand* srcpar = (myCommand*)src->parameters.element;
            /** iterer les paramètres, identifier les noms des paramètres */
            for(int index = 0; index < d->parameters.used; ++index) {
               
                
                if (index < src->parameters.used) {
                    
                    /** recopie le name dans la commande **/
                    writeString(&srcpar[index].name, opar[index].name.strContent);

                }
            }
            
            return true;
            
        }
        else if (optional.used > 1)
        {
            
            fwprintf(stdout, L"Je n'ai pas trouvé la commande %ls %ls avec certitude\n", src->name.strContent, src->option.strContent);
            return false;
            
        }
        else
        {
            fwprintf(stdout, L"Je n'ai pas trouvé la commande %ls %ls\n", src->name.strContent, src->option.strContent);
            return false;

        }

    }
    else
    {

        fwprintf(stdout, L"Je n'ai pas trouvé la commande %ls\n", src->name.strContent);
        return false;

    }
    
}
