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
#include <stdarg.h>
#include "girlParser.h"


/**
 **  Set a list of int
 **/
static int* listInt = NULL;
int* setIntList(int z, ...) {
    
    va_list(ints);
    va_start(ints, z);
    if (listInt != NULL)
        free(listInt);
    listInt = (int*)malloc((z+1) * sizeof(int));
    
    for(int index = 0; index < z; ++index) {
        
        listInt[index] = va_arg(ints, int);
        
    }
    
    va_end(ints);
    return listInt;
}

/**
 **  Set a list of chars
 **/
static wchar_t* listChar = NULL;
wchar_t* setCharList(int z, ...) {
    
    va_list(chars);
    va_start(chars, z);
    if (listChar != NULL)
        free(listChar);
    listChar = (wchar_t*)malloc((z+1) * sizeof(wchar_t));
    
    for(int index = 0; index < z; ++index) {
        
        listChar[index] = va_arg(chars, wchar_t);
        
    }
    
    va_end(chars);
    return listChar;
}

/**
 **   Set a list of actions
 **/
static action* listAction = NULL;
action* setActionList(int z, ...) {
    
    va_list(actions);
    va_start(actions, z);
    if (listAction != NULL)
        free(listAction);
    listAction = (action*)malloc((z+1) * sizeof(action));
    
    for(int index = 0; index < z; ++index) {
        
        listAction[index] = va_arg(actions, action);
        
    }
    
    va_end(actions);
    return listAction;
}


/**
 **   Set a list of string
 **/
myString* setStringList(int z, ...) {
    
    va_list(actions);
    va_start(actions, z);
    myString* tabString = (myString*)malloc((z+1) * sizeof(myString));
    
    for(int index = 0; index < z; ++index) {
        
        myString arg = va_arg(actions, myString);
        tabString[index] = createString(arg.used);
        writeString(&tabString[index], arg.strContent);
        
    }
    
    va_end(actions);
    return tabString;
}

/**
 **   Crée une liste limitée
 **   capacity : capacité maximum
 **/
myLookaheadList createLookaheadList(unsigned int capacity) {
    
    
    myLookaheadList m;
    m.list = (myLookahead*)malloc(sizeof(myLookahead) * (capacity + 1));
    if (m.list != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.list, 0, sizeof(myLookahead));
        return m;
        
    } else {
        
        perror("Erreur dans createLookaheadList : ");
        exit(EXIT_FAILURE);
    }
    
}

/**
 **   Crée une liste limitée
 **   capacity : capacité maximum
 **/
myKeywordList createKeywordList(unsigned int capacity) {
    
    
    myKeywordList m;
    m.keys = (myKeyword*)malloc(sizeof(myKeyword) * (capacity + 1));
    if (m.keys != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.keys, 0, sizeof(myKeyword));
        return m;
        
    } else {
        
        perror("Erreur dans createKeywordList : ");
        exit(EXIT_FAILURE);
    }
    
}

/**
 **   Crée une liste limitée
 **   capacity : capacité maximum
 **/
myAutomaticMoveList createAutomaticMoveList(unsigned int capacity) {
    
    
    myAutomaticMoveList m;
    m.moves = (myAutomaticMove*)malloc(sizeof(myAutomaticMove) * (capacity + 1));
    if (m.moves != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.moves, 0, sizeof(myAutomaticMove));
        return m;
        
    } else {
        
        perror("Erreur dans createAutomaticMoveList : ");
        exit(EXIT_FAILURE);
    }
    
}

/**
 **   Crée une liste limitée
 **   capacity : capacité maximum
 **/
myActionList createActionList(unsigned int capacity) {
    
    
    myActionList m;
    m.actions = (myAction*)malloc(sizeof(myAction) * (capacity + 1));
    if (m.actions != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.actions, 0, sizeof(myAction));
        return m;
        
    } else {
        
        perror("Erreur dans createActionList : ");
        exit(EXIT_FAILURE);
    }
    
}





/**
 **  Create a girl parser
 **
 **/
myGirlParser createGirlParser(int start, int* ends, unsigned int countEnds) {
    
    myGirlParser p;
    
    p.notAvalaible = false;
    p.state_start = start;
    p.countState = countEnds;
    p.state_end = (int*)malloc(sizeof(int) * countEnds);
    memcpy(p.state_end, ends, sizeof(int) * countEnds);
    p.lookaheads = createLookaheadList(0);
    p.keywords = createKeywordList(0);
    p.autoMoves = createAutomaticMoveList(0);
    p.works = createActionList(0);
    
    p.currentState = start;
    p.input = createString(0);

    return p;
}


/**
 **  Create a lookahead
 **
 **/
myLookahead createLookahead(int* states_for, unsigned int countFor, wchar_t* chars, unsigned int countChars, int next) {
    
    myLookahead h;
    
    h.state_for = (int*)malloc(sizeof(int) * countFor);
    h.countState = countFor;
    memcpy(h.state_for, states_for, countFor * sizeof(int));
    h.if_c = (wchar_t*)malloc(sizeof(wchar_t) * countChars);
    h.countChars = countChars;
    memcpy(h.if_c, chars, countChars * sizeof(wchar_t));
    h.state_next = next;
    
    return h;
    
}

/**
 **  Realloc lookahead list
 **
 **/
myLookaheadList* reallocLookahead(myLookaheadList* la, unsigned int newCapacity) {
    
    myLookahead* newAlloc = (myLookahead*)realloc(la->list, sizeof(myLookahead) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        la->list = newAlloc;
        la->capacity = newCapacity;
        return la;
        
    } else {
        
        perror("Erreur dans reallocLookahead");
        exit(EXIT_FAILURE);
        
    }

}

/**
 **   Ecrit dans la liste
 **   indépendamment de la taille nécessaire
 **   myLookaheadList : list
 **   myLookahead : object
 **/
myLookaheadList* writeLookahead(myLookaheadList* m, myLookahead* la) {
    
    if (m->used == 0) {
        
        if (m->capacity < 2) {
            reallocLookahead(m, 2);
        }
        memcpy(&m->list[m->used], la, sizeof(myLookahead));
        m->used = 1;
        
    } else if (m->used + 1 < m->capacity) {
        
        memcpy(&m->list[m->used], la, sizeof(myLookahead));
        m->used += 1;
        
    } else {
        
        reallocLookahead(m, m->capacity + MINSIZE);
        memcpy(&m->list[m->used], la, sizeof(myLookahead));
        m->used += 1;
    
    }
    
    return m;
    
}


/**
 **   Add lookahead
 **
 **/
void addLookahead(myGirlParser* girl, int* states_for, unsigned int countFor, wchar_t* chars, unsigned int countChars, int next) {
    
    myLookahead h = createLookahead(states_for, countFor, chars, countChars, next);
    writeLookahead(&girl->lookaheads, &h);
    
}

/**
 **  Create a keyword
 **
 **/
myKeyword createKeyword(int* states_for, unsigned int countFor, myString* sList, unsigned int countString, int next) {
    
    myKeyword h;
    
    h.state_for = (int*)malloc(sizeof(int) * countFor);
    h.countState = countFor;
    memcpy(h.state_for, states_for, countFor * sizeof(int));
    h.if_s = (myString*)malloc(sizeof(myString) * countString);
    h.countChars = countString;
    for(int index = 0; index < countString; ++index) {
        
        h.if_s[index] = createString(sList[index].used);
        writeString(&h.if_s[index], sList[index].strContent);
        
    }
    h.state_next = next;
    
    return h;
    
}

/**
 **  Realloc keyword list
 **
 **/
myKeywordList* reallocKeyword(myKeywordList* la, unsigned int newCapacity) {
    
    myKeyword* newAlloc = (myKeyword*)realloc(la->keys, sizeof(myKeyword) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        la->keys = newAlloc;
        la->capacity = newCapacity;
        return la;
        
    } else {
        
        perror("Erreur dans reallocKeyword");
        exit(EXIT_FAILURE);
        
    }
    
}

/**
 **   Ecrit dans la liste
 **   indépendamment de la taille nécessaire
 **   myKeywordList : list
 **   myKeyword : object
 **/
myKeywordList* writeKeyword(myKeywordList* m, myKeyword* la) {
    
    if (m->used == 0) {
        
        if (m->capacity < 2) {
            reallocKeyword(m, 2);
        }
        memcpy(&m->keys[m->used], la, sizeof(myKeyword));
        m->used = 1;
        
    } else if (m->used + 1 < m->capacity) {
        
        memcpy(&m->keys[m->used], la, sizeof(myKeyword));
        m->used += 1;
        
    } else {
        
        reallocKeyword(m, m->capacity + MINSIZE);
        memcpy(&m->keys[m->used], la, sizeof(myKeyword));
        m->used += 1;
        
    }
    
    return m;
    
}


/**
 **   Add keyword
 **
 **/
void addKeyword(myGirlParser* girl, int* states_for, unsigned int countFor, myString* strList, unsigned int countString, int next) {
    
    myKeyword h = createKeyword(states_for, countFor, strList, countString, next);
    writeKeyword(&girl->keywords, &h);
    
}



/**
 **  Create an automatic move
 **
 **/
myAutomaticMove createAutomaticMove(int* states_from, unsigned int countFrom, int next) {
    
    myAutomaticMove h;
    
    h.state_from = (int*)malloc(sizeof(int) * countFrom);
    h.countState = countFrom;
    memcpy(h.state_from, states_from, countFrom * sizeof(int));
    h.state_to = next;
    
    return h;
    
}

/**
 **  Realloc automatic move list
 **
 **/
myAutomaticMoveList* reallocAutomaticMove(myAutomaticMoveList* la, unsigned int newCapacity) {
    
    myAutomaticMove* newAlloc = (myAutomaticMove*)realloc(la->moves, sizeof(myAutomaticMove) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        la->moves = newAlloc;
        la->capacity = newCapacity;
        return la;
        
    } else {
        
        perror("Erreur dans reallocAutomaticMove");
        exit(EXIT_FAILURE);
        
    }
    
}

/**
 **   Ecrit dans la liste
 **   indépendamment de la taille nécessaire
 **   myAutomaticMoveList : list
 **   myAutomaticMove : object
 **/
myAutomaticMoveList* writeAutomaticMove(myAutomaticMoveList* m, myAutomaticMove* la) {
    
    if (m->used == 0) {
        
        if (m->capacity < 2) {
            reallocAutomaticMove(m, 2);
        }
        memcpy(&m->moves[m->used], la, sizeof(myAutomaticMove));
        m->used = 1;
        
    } else if (m->used + 1 < m->capacity) {
        
        memcpy(&m->moves[m->used], la, sizeof(myAutomaticMove));
        m->used += 1;
        
    } else {
        
        reallocAutomaticMove(m, m->capacity + MINSIZE);
        memcpy(&m->moves[m->used], la, sizeof(myAutomaticMove));
        m->used += 1;
        
    }
    
    return m;
    
}


/**
 **   Add automatic move
 **
 **/
void addAutomaticMove(myGirlParser* girl, int* states_from, unsigned int countFrom, int next) {
    
    myAutomaticMove h = createAutomaticMove(states_from, countFrom, next);
    writeAutomaticMove(&girl->autoMoves, &h);
    
}


/**
 **  Create an action
 **
 **/
myAction createAction(int* states_at, unsigned int countAt, action* f, unsigned int countF) {
    
    myAction h;
    
    h.states_at = (int*)malloc(sizeof(int) * countAt);
    h.countState = countAt;
    memcpy(h.states_at, states_at, countAt * sizeof(int));
    h.functions = (action*)malloc(sizeof(action) * countF);
    h.countFunctions = countF;
    for(int index = 0; index < countF; ++index) {
        
        h.functions[index] = f[index];
        
    }

    return h;
    
}

/**
 **  Realloc action list
 **
 **/
myActionList* reallocAction(myActionList* la, unsigned int newCapacity) {
    
    myAction* newAlloc = (myAction*)realloc(la->actions, sizeof(myAction) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        la->actions = newAlloc;
        la->capacity = newCapacity;
        return la;
        
    } else {
        
        perror("Erreur dans reallocAction");
        exit(EXIT_FAILURE);
        
    }
    
}

/**
 **   Ecrit dans la liste
 **   indépendamment de la taille nécessaire
 **   myActionList : list
 **   myAction : object
 **/
myActionList* writeAction(myActionList* m, myAction* la) {
    
    if (m->used == 0) {
        
        if (m->capacity < 2) {
            reallocAction(m, 2);
        }
        memcpy(&m->actions[m->used], la, sizeof(myAction));
        m->used = 1;
        
    } else if (m->used + 1 < m->capacity) {
        
        memcpy(&m->actions[m->used], la, sizeof(myAction));
        m->used += 1;
        
    } else {
        
        reallocAction(m, m->capacity + MINSIZE);
        memcpy(&m->actions[m->used], la, sizeof(myAction));
        m->used += 1;
        
    }
    
    return m;
    
}


/**
 **   Add action
 **
 **/
void addAction(myGirlParser* girl, int* states_at, unsigned int countAt, action* f, unsigned int countF) {
    
    myAction h = createAction(states_at, countAt, f, countF);
    writeAction(&girl->works, &h);
    
}

/**
 **  Search lookahead next state
 **/
bool searchLookahead(myGirlParser* p, int state, wchar_t c, int* next) {
    
    bool found = false;
    for(int index = 0; index < p->lookaheads.used && !found; ++index) {
        
        myLookahead* l = &p->lookaheads.list[index];
        for(int stateIndex = 0; stateIndex < l->countState && !found; ++stateIndex) {
            
            if (l->state_for[stateIndex] == state) {
                
                for(int charIndex = 0; charIndex < l->countChars && !found; ++charIndex) {
                    
                    if (l->if_c[charIndex] == c) {
                        found = true;
                        *next = l->state_next;
                    }
                    
                }

            }
            
        }
        
    }
    
    return found;
    
}

/**
 **  Search automatic next state
 **/
bool searchAutomaticMove(myGirlParser* p, int state, int* next) {
    
    bool found = false;
    for(int index = 0; index < p->autoMoves.used && !found; ++index) {
        
        myAutomaticMove* l = &p->autoMoves.moves[index];
        for(int stateIndex = 0; stateIndex < l->countState && !found; ++stateIndex) {
            
            if (l->state_from[stateIndex] == state) {
                
                found = true;
                *next = l->state_to;
                
            }
        }
        
    }
    
    return found;
    
}

/**
 **  Search actions and execute them
 **/
bool searchAction(myGirlParser* p, int state, action** f, unsigned int* countFunctions) {
    
    bool found = false;
    for(int index = 0; index < p->works.used && !found; ++index) {
        
        myAction* l = &p->works.actions[index];
        for(int stateIndex = 0; stateIndex < l->countState && !found; ++stateIndex) {
            
            if (l->states_at[stateIndex] == state) {
                
                found = true;
                *f = (action*)malloc(sizeof(myAction) * l->countFunctions);
                *countFunctions = l->countFunctions;
                for(int index = 0; index < *countFunctions; ++index) {
                    
                    (*f)[index] = l->functions[index];
                    
                }

            }
        }
        
    }
    
    return found;
    
}


bool process(myGirlParser* p, myString* s, void* object) {

    clearString(&p->input);
    writeString(&p->input, s->strContent);
    p->currentIndex = 0;
    int next;
    
    while(p->currentIndex < p->input.used && !p->notAvalaible) {
    
        /** lookahead **/
        if (searchLookahead(p, p->currentState, p->input.strContent[p->currentIndex], &next)) {
            
            /** changement d'état **/
            p->currentState = next;
            continue;
            
        }
    
        /** launch actions **/
        action* a = NULL;
        unsigned int count;
        if (searchAction(p, p->currentState, &a, &count)) {
            
            action* current = a;
            for(int countF = 0; countF < count; ++countF, ++current) {
                
                (*current)(p, object);
                
            }
            free(a);
        }

        /** automatic moves **/
        if (searchAutomaticMove(p, p->currentState, &next)) {
            
            /** changement d'état **/
            p->currentState = next;
            continue;
            
        }
    
        for(int endIndex = 0; endIndex < p->countState; ++endIndex) {
            
            if (p->state_end[endIndex] == p->currentState) {
                
                p->notAvalaible = true;
                
            }
            
        }
    }

    return !p->notAvalaible;
}
