//
//  dataModel.c
//  generatic
//
//  Created by Olivier on 16/08/2018.
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
 **   Crée une liste de couples name/value limitée
 **   capacity : capacité maximum
 **/
myValueKeyList createValueKeyList(unsigned int capacity) {
    
    
    myValueKeyList m;
    m.element = (myValueKey*)malloc(sizeof(myValueKey) * (capacity + 1));
    if (m.element != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.element, 0, sizeof(myValueKey));
        return m;
        
    } else {
        
        perror("Erreur dans createValueKeyList : ");
        exit(EXIT_FAILURE);
    }
    
}

/**
 **   Crée une liste de commandes limitée
 **   capacity : capacité maximum
 **/
myCommandList createCommandList(unsigned int capacity) {
    
    
    myCommandList m;
    m.element = (myCommand*)malloc(sizeof(myCommand) * (capacity + 1));
    if (m.element != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.element, 0, sizeof(myCommand));
        return m;
        
    } else {
        
        perror("Erreur dans createCommandList : ");
        exit(EXIT_FAILURE);
    }
    
}

/**
 **   Crée une liste d'indentation limitée
 **   capacity : capacité maximum
 **/
myTabList createTabList(unsigned int capacity) {
    
    
    myTabList m;
    m.lineNumbers = (unsigned int*)malloc(sizeof(unsigned int) * (capacity + 1));
    if (m.lineNumbers != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.lineNumbers, 0, sizeof(unsigned int));
        return m;
        
    } else {
        
        perror("Erreur dans createTabList : ");
        exit(EXIT_FAILURE);
    }
    
}

/**
 **   Crée une liste de sessions limitée
 **   capacity : capacité maximum
 **/
mySessionList createSessionList(unsigned int capacity) {
    
    
    mySessionList m;
    m.sx = (mySession*)malloc(sizeof(mySession) * (capacity + 1));
    if (m.sx != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.sx, 0, sizeof(mySession));
        return m;
        
    } else {
        
        perror("Erreur dans createSessionList : ");
        exit(EXIT_FAILURE);
    }
    
}


/**
 **   Libère la mémoire
 **   myValueKey : données
 **/
void freeValueKey(myValueKey* d) {
    
    freeData(&d->name);
    freeData(&d->value);
}

/**
 **   Libère la mémoire
 **   myCommand : données
 **/
void freeCommand(myCommand* d) {
    
    freeData(&d->name);
    freeData(&d->option);
    freeCommandList(&d->parameters);
}

/**
 **   Libère la mémoire
 **   mySession : données
 **/
void freeSession(mySession* d) {
    
    freeData(&d->currentProject.path);
    freeData(&d->currentProject.name);
    freeData(&d->currentFile.path);
    freeData(&d->currentFile.name);
    freeData(&d->language);
    freeCommandList(&d->commands);
}


/**
 **   Libère la mémoire
 **   myValueKeyList : données
 **/
void freeValueKeyList(myValueKeyList* l) {
    
    myValueKey* current = l->element;
    
    int index;
    for(index = 0; index < l->used; ++index,++current) {
        
        freeValueKey(current);
        
    }
    
    free(l->element);
    l->capacity = 0;
    l->used = 0;
    
}

/**
 **   Libère la mémoire
 **   myCommandList : données
 **/
void freeCommandList(myCommandList* l) {
    
    myCommand* current = l->element;
    
    int index;
    for(index = 0; index < l->used; ++index,++current) {
        
        freeCommand(current);
        
    }
    
    free(l->element);
    l->capacity = 0;
    l->used = 0;
    
}

/**
 **   Libère la mémoire
 **   myTabList : données
 **/
void freeTabList(myTabList* l) {
    
    free(l->lineNumbers);
    l->capacity = 0;
    l->used = 0;
    
}

/**
 **   Libère la mémoire
 **   mySessionList : données
 **/
void freeSessionList(mySessionList* l) {
    
    mySession* current = l->sx;
    
    int index;
    for(index = 0; index < l->used; ++index,++current) {
        
        freeSession(current);
        
    }
    
    free(l->sx);
    l->capacity = 0;
    l->used = 0;
    
}


/**
 **   Augmente la taille de la liste
 **   myValueKeyList : liste en entrée
 **   newCapacity : nouvelle capacité maximum
 **/
myValueKeyList* reallocValueKeyList(myValueKeyList* m, unsigned int newCapacity) {
    
    myValueKey* newAlloc = (myValueKey*)realloc(m->element, sizeof(myValueKey) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        m->element = newAlloc;
        m->capacity = newCapacity;
        return m;
        
    } else {
        
        perror("Erreur dans reallocValueKeyList");
        exit(EXIT_FAILURE);
        
    }
    
}


/**
 **   Augmente la taille de la liste
 **   myCommandList : liste en entrée
 **   newCapacity : nouvelle capacité maximum
 **/
myCommandList* reallocCommandList(myCommandList* m, unsigned int newCapacity) {
    
    myCommand* newAlloc = (myCommand*)realloc(m->element, sizeof(myCommand) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        m->element = newAlloc;
        m->capacity = newCapacity;
        return m;
        
    } else {
        
        perror("Erreur dans reallocCommandList");
        exit(EXIT_FAILURE);
        
    }
    
}


/**
 **   Augmente la taille de la liste
 **   myTabList : liste en entrée
 **   newCapacity : nouvelle capacité maximum
 **/
myTabList* reallocTabList(myTabList* m, unsigned int newCapacity) {
    
    unsigned int* newAlloc = (unsigned int*)realloc(m->lineNumbers, sizeof(unsigned int) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        m->lineNumbers = newAlloc;
        m->capacity = newCapacity;
        return m;
        
    } else {
        
        perror("Erreur dans reallocTabList");
        exit(EXIT_FAILURE);
        
    }
    
}


/**
 **   Augmente la taille de la liste
 **   mySessionList : liste en entrée
 **   newCapacity : nouvelle capacité maximum
 **/
mySessionList* reallocSessionList(mySessionList* m, unsigned int newCapacity) {
    
    mySession* newAlloc = (mySession*)realloc(m->sx, sizeof(mySession) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        m->sx = newAlloc;
        m->capacity = newCapacity;
        return m;
        
    } else {
        
        perror("Erreur dans reallocSessionList");
        exit(EXIT_FAILURE);
        
    }
    
}



/**
 **   Supprime un élément de l'index
 **   myValueKeyList : liste en entrée
 **   index : position à supprimer
 **/
myValueKeyList* removeAtValueKeyList(myValueKeyList* m, unsigned int index) {
    
    if (index < m->used) {
        
        for(int counter = index + 1; counter < m->used; ++counter) {
            
            m->element[counter - 1] = m->element[counter];
            
        }
        return m;
        
    } else {
        
        perror("Erreur dans removeAtValueKeyList");
        exit(EXIT_FAILURE);
        
    }
    
}


/**
 **   Supprime un élément de l'index
 **   myCommandList : liste en entrée
 **   index : position à supprimer
 **/
myCommandList* removeAtCommandList(myCommandList* m, unsigned int index) {
    
    if (index < m->used) {
        
        for(int counter = index + 1; counter < m->used; ++counter) {
            
            memcpy(m->element + (counter - 1), m->element + counter, sizeof(myCommand));
            
        }
        return m;
        
    } else {
        
        perror("Erreur dans removeAtCommandList");
        exit(EXIT_FAILURE);
        
    }
    
}


/**
 **   Supprime un élément de l'index
 **   myTabList : liste en entrée
 **   index : position à supprimer
 **/
myTabList* removeAtTabList(myTabList* m, unsigned int index) {
    
    if (index < m->used) {
        
        for(int counter = index + 1; counter < m->used; ++counter) {
            
            m->lineNumbers[counter - 1] = m->lineNumbers[counter];
            
        }
        return m;
        
    } else {
        
        perror("Erreur dans removeAtTabList");
        exit(EXIT_FAILURE);
        
    }
    
}



/**
 **   Supprime un élément de l'index
 **   mySessionList : liste en entrée
 **   index : position à supprimer
 **/
mySessionList* removeAtSessionList(mySessionList* m, unsigned int index) {
    
    if (index < m->used) {
        
        for(int counter = index + 1; counter < m->used; ++counter) {
            
            m->sx[counter - 1] = m->sx[counter];
            
        }
        return m;
        
    } else {
        
        perror("Erreur dans removeAtSessionList");
        exit(EXIT_FAILURE);
        
    }
    
}



/**
 **   Crée un tuple nom/valeur
 **/
myValueKey createValueKey() {
    
    myValueKey k;
    k.name = createData(MINSIZE);
    k.value = createData(MINSIZE);
    
    return k;
    
}


/**
 **   Crée une commande
 **/
myCommand createCommand() {
    
    myCommand k;
    k.name = createData(MINSIZE);
    k.option = createData(MINSIZE);
    k.parameters = createCommandList(MINSIZE);
    
    return k;
    
}


/**
 **   Crée une session
 **/
mySession createSession() {
    
    mySession k;
    k.currentProject.path = createData(MINSIZE);
    k.currentProject.name = createData(MINSIZE);
    k.currentFile.path = createData(MINSIZE);
    k.currentFile.name = createData(MINSIZE);
   
    k.language = createData(MINSIZE);
    
    k.commands = createCommandList(MINSIZE);
    
    return k;
    
}





