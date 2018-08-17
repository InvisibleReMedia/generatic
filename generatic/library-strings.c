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


/**
 **   Hack to do not read
 **   \r
 **
 **/
wchar_t nonDosFormat(FILE* io) {
    
    wchar_t c = fgetwc(io);
    if (c == '\r')
        c = fgetwc(io);
    return c;
    
}

/**
 **   Crée une liste limitée
 **   capacity : capacité maximum
 **/
myList createList(unsigned int capacity) {
    
    
    myList m;
    m.list = (myKey*)malloc(sizeof(myKey) * (capacity + 1));
    if (m.list != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.list, 0, sizeof(myKey));
        return m;
        
    } else {
        
        perror("Erreur dans createList : ");
        exit(EXIT_FAILURE);
    }
    
}


/**
 **   Crée une zone de mémoire limitée
 **   capacity : capacité maximum
 **/
myString createString(unsigned int capacity) {
    
    
    myString m;
    m.strContent = (wchar_t*)malloc(sizeof(wchar_t) * (capacity + 1));
    if (m.strContent != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        *(m.strContent) = '\0';
        assert(wcslen(m.strContent) == 0);
        return m;
        
    } else {
        
        perror("Erreur dans createString : ");
        exit(EXIT_FAILURE);
    }
    
}

/**
 **   Libère la mémoire
 **   myString : données
 **/
void freeString(myString* d) {
    
    free(d->strContent);
    d->used = 0;
    d->capacity = 0;
}


/**
 **   Crée un tuple nom/valeur
 **   capacity : capacité maximum
 **/
myKey createKey() {
    
    myKey k;
    k.question.strContent = (wchar_t*)malloc(sizeof(wchar_t) * (MINSIZE + 1));
    *(k.question.strContent) = '\0';
    assert(wcslen(k.question.strContent) == 0);
    k.question.used = 0;
    k.question.capacity = MINSIZE;
    
    k.name.strContent = (wchar_t*)malloc(sizeof(wchar_t) * (MINSIZE + 1));
    *(k.name.strContent) = '\0';
    assert(wcslen(k.name.strContent) == 0);
    k.name.used = 0;
    k.name.capacity = MINSIZE;
    
    k.value.strContent = (wchar_t*)malloc(sizeof(wchar_t) * (MINSIZE + 1));
    *(k.value.strContent) = '\0';
    assert(wcslen(k.value.strContent) == 0);
    k.value.used = 0;
    k.value.capacity = MINSIZE;
    
    return k;
    
}

/**
 **   Libère la mémoire
 **   myKey : données
 **/
void freeKey(myKey* k) {
    
    freeString(&k->name);
    freeString(&k->value);
    freeString(&k->question);
}

/**
 **   Libère la mémoire
 **   myList : données
 **/
void freeList(myList* l) {
    
    myKey* current = l->list;
    
    int index;
    for(index = 0; index < l->used; ++index,++current) {
        
        freeKey(current);
        
    }
    
    free(l->list);
    l->capacity = 0;
    l->used = 0;
    
}

/**
 **   Compare deux zones de mémoires
 **   current : zone où chercher
 **   search : texte de recherche
 **/
int compareString(myString current, myString search) {
    
    int t = wcscmp(current.strContent, search.strContent);
    if (t == 0) {
        
        return 0;
        
    } else if (t > 0) {
        
        return 1;
        
    } else {
        
        return -1;
        
    }
}

/**
 **   Augmente la taille de la liste
 **   myList : liste en entrée
 **   newCapacity : nouvelle capacité maximum
 **/
myList* reallocList(myList* m, unsigned int newCapacity) {
    
    myKey* newAlloc = (myKey*)realloc(m->list, sizeof(myKey) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        m->list = newAlloc;
        m->capacity = newCapacity;
        return m;
        
    } else {
        
        perror("Erreur dans reallocData");
        exit(EXIT_FAILURE);
        
    }
    
}

/**
 **   Augmente la capacité de la zone de mémoire
 **   myString : zone de mémoire
 **   newCapacity : nouvelle capacité maximum
 **/
myString* reallocData(myString* m, unsigned int newCapacity) {
    
    wchar_t* newAlloc = realloc(m->strContent, sizeof(wchar_t) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        m->strContent = newAlloc;
        m->capacity = newCapacity;
        return m;
        
    } else {
        
        perror("Erreur dans reallocData");
        exit(EXIT_FAILURE);
        
    }
    
}

/**
 **   Ecrit dans la zone de mémoire
 **   indépendamment de la taille nécessaire
 **   myString : zone de mémoire
 **   strContent : contenu à ajouter
 **/
myString* writeString(myString* m, wchar_t* strContent) {
    
    unsigned int l = (unsigned int)wcslen(strContent);
    
    if (l > 0) {
        
        if (m->used == 0) {
            
            assert(wcslen(m->strContent) == 0);
            if (m->capacity < l + 1) {
                if (l < MINSIZE)
                    reallocData(m, m->capacity + MINSIZE);
                else
                    reallocData(m, m->capacity + l + 1);
            }
            wcscat(m->strContent, strContent);
            m->used = l;
            assert(wcslen(m->strContent) == m->used);
            
        } else if (m->used + l + 1 < m->capacity) {
            
            wcscat(m->strContent, strContent);
            m->used += l;
            assert(wcslen(m->strContent) == m->used);
            
        } else {
            
            assert(wcslen(m->strContent) == m->used);
            if (l < MINSIZE)
                reallocData(m, m->capacity + MINSIZE);
            else
                reallocData(m, m->capacity + l);
            wcscat(m->strContent, strContent);
            m->used += l;
            assert(wcslen(m->strContent) == m->used);
            
        }
        
    }
    
    return m;
    
}


/**
 **   Ecrit dans la liste
 **   indépendamment de la taille nécessaire
 **   myList : list
 **   text : texte de la question
 **   strName : nom de code
 **   value : valeur
 **/
myList* writeList(myList* m, wchar_t *text, wchar_t* strName, wchar_t* value) {
    
    myKey* current = m->list;
    myString d = createString((unsigned int)wcslen(strName));
    writeString(&d, strName);
    
    bool found = false;
    int index;
    for(index = 0; index < m->used && !found; ++index,++current) {
        
        if (compareString(current->name, d) == 0) {
            
            writeString(&current->value, value);
            found = true;
            
        }
        
    }
    
    if(!found) {
        
        myKey k = createKey();
        writeString(&k.question, text);
        writeString(&k.name, strName);
        writeString(&k.value, value);
        
        if (m->used == 0) {
            
            if (m->capacity < 2) {
                reallocList(m, 2);
            }
            m->list[m->used] = k;
            m->used = 1;
            
        } else if (m->used + 1 < m->capacity) {
            
            m->list[m->used] = k;
            m->used += 1;
            
        } else {
            
            reallocList(m, m->capacity + MINSIZE);
            m->list[m->used] = k;
            m->used += 1;
            
        }
        
    }
    
    freeString(&d);
    
    return m;
    
}

/**
 **   Recherche dans la liste
 **   myList : list
 **   strName : nom de code
 **   returns string content
 **/
wchar_t* search(myList* m, wchar_t* strName) {
    
    myKey* current = m->list;
    myString d = createString((unsigned int)wcslen(strName));
    writeString(&d, strName);
    
    bool found = false;
    int index;
    for(index = 0; index < m->used && !found; ++index,++current) {
        
        if (compareString(current->name, d) == 0) {
            
            found = true;
            break;
            
        }
        
    }
    
    freeString(&d);
    
    if (found) {
        
        return current->value.strContent;
        
    }
    
    return L"";
    
    
}



/**
 **   Efface un fichier
 **   strfName : nom du fichier
 **/
void eraseFile(char* strfName) {
    
    remove(strfName);
    
}

/**
 **   Ecrit dans un fichier
 **   strfName : nom du fichier
 **   strContent : texte à écrire
 **/
void writeFile(char *destfName, writeLine f) {
    
    myString line;
    FILE* writeFile = NULL;
    
    line = createString(MINSIZE);
    
    eraseFile(destfName);
    
        if ((writeFile = fopen(destfName, "w")) != NULL) {
            
            bool result;
            do {

                memset(line.strContent, 0, line.used);
                line.used = 0;
                result = f(&line);
                fwprintf(writeFile, L"%s\n", line.strContent);
                
            } while(!result);

            fclose(writeFile);
            
        } else {
            
            perror("Fichier en erreur :");
        }
        
    freeString(&line);
    
}




