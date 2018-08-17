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
    
    freeString(&d->name);
    freeString(&d->value);
}

/**
 **   Libère la mémoire
 **   myCommand : données
 **/
void freeCommand(myCommand* d) {
    
    freeString(&d->name);
    freeString(&d->option);
    freeString(&d->value);
    freeCommandList(&d->parameters);
}

/**
 **   Libère la mémoire
 **   mySession : données
 **/
void freeSession(mySession* d) {
    
    freeString(&d->currentProject.path);
    freeString(&d->currentProject.name);
    freeString(&d->currentFile.path);
    freeString(&d->currentFile.name);
    freeString(&d->language);
    freeCommandList(&d->commands);
}

/**
 **   Libère la mémoire
 **   myModel : données
 **/
void freeModel(myModel* d) {
    
    freeValueKeyList(&d->config);
    freeSessionList(&d->sessions);
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
        --m->used;
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
            
            myCommand* p = (myCommand*)m->element;
            p[counter - 1] = p[counter];
            
        }
        --m->used;
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
        --m->used;
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
        --m->used;
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
    k.name = createString(MINSIZE);
    k.value = createString(MINSIZE);
    
    return k;
    
}


/**
 **   Crée une commande
 **/
myCommand createCommand() {
    
    myCommand k;
    k.name = createString(MINSIZE);
    k.option = createString(MINSIZE);
    k.value = createString(MINSIZE);
    k.parameters = createCommandList(0);
    
    return k;
    
}


/**
 **   Crée une session
 **/
mySession createSession() {
    
    mySession k;
    k.currentProject.path = createString(MINSIZE);
    k.currentProject.name = createString(MINSIZE);
    k.currentFile.path = createString(MINSIZE);
    k.currentFile.name = createString(MINSIZE);
   
    k.language = createString(MINSIZE);
    k.commands = createCommandList(0);
    
    return k;
    
}

/**
 **   Crée un projet
 **/
myModel createModel() {
    
    myModel k;
    
    k.config = createValueKeyList(MINSIZE);
    k.sessions = createSessionList(1);
    mySession s = createSession();
    writeSession(&k.sessions, &s);
    k.currentSession = &(k.sessions.sx[0]);
    
    
    return k;
    
}

/**
 **   Ecrit dans la zone de mémoire
 **   indépendamment de la taille nécessaire
 **   myValueKeyList : zone de mémoire
 **   myValueKey : contenu à ajouter
 **/
myValueKeyList* writeValueKey(myValueKeyList* m, myValueKey* key) {
    

    if (m->used == 0) {
        
        if (m->capacity < 2) {
            reallocValueKeyList(m, 2);
        }
        m->element[m->used] = *key;
        m->used = 1;
        
    } else if (m->used + 1 < m->capacity) {
        
        m->element[m->used] = *key;
        m->used += 1;
        
    } else {
        
        reallocValueKeyList(m, m->capacity + MINSIZE);
        m->element[m->used] = *key;
        m->used += 1;
        
    }
    
    return m;
    
}


/**
 **   Ecrit dans la zone de mémoire
 **   indépendamment de la taille nécessaire
 **   myTabList : zone de mémoire
 **   u : contenu à ajouter
 **/
myTabList* writeTab(myTabList* m, unsigned int u) {
    
    
    if (m->used == 0) {
        
        if (m->capacity < 2) {
            reallocTabList(m, 2);
        }
        m->lineNumbers[m->used] = u;
        m->used = 1;
        
    } else if (m->used + 1 < m->capacity) {
        
        m->lineNumbers[m->used] = u;
        m->used += 1;
        
    } else {
        
        reallocTabList(m, m->capacity + MINSIZE);
        m->lineNumbers[m->used] = u;
        m->used += 1;
        
    }
    
    return m;
    
}


/**
 **   Ecrit dans la zone de mémoire
 **   indépendamment de la taille nécessaire
 **   myCommandList : zone de mémoire
 **   c : contenu à ajouter
 **/
myCommandList* writeCommand(myCommandList* m, myCommand* c) {
    
    
    if (m->used == 0) {
        
        if (m->capacity < 2) {
            reallocCommandList(m, 2);
        }
        myCommand* p = (myCommand*)m->element;
        p[m->used] = *c;

        m->used = 1;
        
    } else if (m->used + 1 < m->capacity) {
        
        myCommand* p = (myCommand*)m->element;
        p[m->used] = *c;
        m->used += 1;
        
    } else {
        
        reallocCommandList(m, m->capacity + MINSIZE);
        myCommand* p = (myCommand*)m->element;
        p[m->used] = *c;
        m->used += 1;
        
    }
    
    return m;
    
}




/**
 **   Ecrit dans la zone de mémoire
 **   indépendamment de la taille nécessaire
 **   mySessionList : zone de mémoire
 **   s : contenu à ajouter
 **/
mySessionList* writeSession(mySessionList* m, mySession* s) {
    
    
    if (m->used == 0) {
        
        if (m->capacity < 2) {
            reallocSessionList(m, 2);
        }
        m->sx[m->used] = *s;
        m->used = 1;
        
    } else if (m->used + 1 < m->capacity) {
        
        m->sx[m->used] = *s;
        m->used += 1;
        
    } else {
        
        reallocSessionList(m, m->capacity + MINSIZE);
        m->sx[m->used] = *s;
        m->used += 1;
        
    }
    
    return m;
    
}

