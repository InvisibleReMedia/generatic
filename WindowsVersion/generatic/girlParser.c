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
#include "Unix/fileSystem.h"
#include <stdarg.h>
#include "exInterpret.h"
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
 **   Set a list of functional
 **/
static interpret* listFunctional = NULL;
interpret* setFunctionalList(int z, ...) {
    
    va_list(functions);
    va_start(functions, z);
    if (listFunctional != NULL)
        free(listFunctional);
    listFunctional = (interpret*)malloc((z+1) * sizeof(interpret));
    
    for(int index = 0; index < z; ++index) {
        
        listFunctional[index] = va_arg(functions, interpret);
        
    }
    
    va_end(functions);
    return listFunctional;
}

/**
 **   Set a list of string
 **/
static myString* listString = NULL;
static int listStringSize = 0;
myString* setStringList(int z, ...) {
    
    va_list(strings);
	va_start(strings, z);
	if (listString != NULL) {

		for (int index = 0; index < listStringSize; ++index)
			freeString(&listString[index]);
		free(listString);
	}
	listString = (myString*)malloc((z + 1) * sizeof(myString));
    
    for(int index = 0; index < z; ++index) {
        
		wchar_t* arg = va_arg(strings, wchar_t*);
		listString[index] = createString((unsigned int)wcslen(arg));
		writeString(&listString[index], arg);
        
    }
    
	va_end(strings);
	return listString;
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
myFunctionalList createFunctionalList(unsigned int capacity) {
    
    
    myFunctionalList m;
    m.funs = (myFunctional*)malloc(sizeof(myFunctional) * (capacity + 1));
    if (m.funs != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.funs, 0, sizeof(myFunctional));
        return m;
        
    } else {
        
        perror("Erreur dans createFunctionalList : ");
        exit(EXIT_FAILURE);
    }
    
}


/**
**   Crée une liste limitée
**   capacity : capacité maximum
**/
myContext createContext(unsigned int capacity) {


	myContext m;
	m.ints = (int*)malloc(sizeof(int) * (capacity + 1));
	if (m.ints != NULL) {

		m.capacity = capacity;
		m.used = 0;
		memset(m.ints, 0, sizeof(int));
		return m;

	}
	else {

		perror("Erreur dans createContext : ");
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
**   Crée une liste limitée
**   capacity : capacité maximum
**/
myRuleList createRuleList(unsigned int capacity) {


	myRuleList m;
	m.list = (myRule*)malloc(sizeof(myRule) * (capacity + 1));
	if (m.list != NULL) {

		m.capacity = capacity;
		m.used = 0;
		memset(m.list, 0, sizeof(myRule));
		return m;

	}
	else {

		perror("Erreur dans createRuleList : ");
		exit(EXIT_FAILURE);
	}

}



/**  
 **  Libère la mémoire
 **  myLookaheadList : data
 **/
void freeLookaheadList(myLookaheadList* p) {

	myLookahead* current = p->list;

	int index;
	for (index = 0; index < p->used; ++index, ++current) {

		freeLookahead(current);

	}

	free(p->list);
	p->capacity = 0;
	p->used = 0;

}


/**
**  Libère la mémoire
**  myRuleList : data
**/
void freeRuleList(myRuleList* p) {

	myRule* current = p->list;

	int index;
	for (index = 0; index < p->used; ++index, ++current) {

		freeRule(current);

	}

	free(p->list);
	p->capacity = 0;
	p->used = 0;

}

void freeContext(myContext* p) {

	free(p->ints);
	p->used = 0;
	p->capacity = 0;
	p->ints = NULL;
}


/**
 **  Libère la mémoire
 **  myKeywordList : data
 **/
void freeKeywordList(myKeywordList* p) {

	myKeyword* current = p->keys;

	int index;
	for (index = 0; index < p->used; ++index, ++current) {

		freeKeyword(current);

	}

	free(p->keys);
	p->capacity = 0;
	p->used = 0;

}

/**
**  Libère la mémoire
**  myAutomaticMoveList : data
**/
void freeAutomaticMoveList(myAutomaticMoveList* p) {

	myAutomaticMove* current = p->moves;

	int index;
	for (index = 0; index < p->used; ++index, ++current) {

		freeAutomaticMove(current);

	}

	free(p->moves);
	p->capacity = 0;
	p->used = 0;

}

/**
**  Libère la mémoire
**  myActionList : data
**/
void freeActionList(myActionList* p) {

	myAction* current = p->actions;

	int index;
	for (index = 0; index < p->used; ++index, ++current) {

		freeAction(current);

	}

	free(p->actions);
	p->capacity = 0;
	p->used = 0;

}



/**
 **  Create a girl parser
 **
 **/
myGirlParser createGirlParser(int start, int* ends, unsigned int countEnds, myString significantChars) {
    
    myGirlParser p;
    
    p.notAvailable = false;
    p.state_start = start;
    p.countState = countEnds;
    p.state_end = (int*)malloc(sizeof(int) * countEnds);
    memcpy(p.state_end, ends, sizeof(int) * countEnds);
    p.lookaheads = createLookaheadList(0);
    p.keywords = createKeywordList(0);
    p.autoMoves = createAutomaticMoveList(0);
    p.works = createActionList(0);
	p.rules = createRuleList(0);
	p.contexts = createContext(0);
    p.functionals = createFunctionalList(0);
    
    p.currentState = start;
	p.significantChars = createString(significantChars.used);
	writeString(&p.significantChars, significantChars.strContent);

    return p;
}

/**
 **   Init a girl parser from a string input
 **/
myGirlParser* initStringGirlParser(myGirlParser* p, myYieldReadPart* y, myString s) {
    
    p->reader = y;
    y->file = NULL;
    y->line = createString(0);
    writeString(&y->line, s.strContent);
    y->pos = 0;
    return p;
}

/**
 **   Init a girl parser from a file input
 **/
myGirlParser* initFileGirlParser(myGirlParser* p, myYieldReadPart* y) {
    
    p->reader = y;
    return p;
}


/**
 **
 **  Libère la mémoire
 **  myGirlParser : data
 **/
void freeGirlParser(myGirlParser* p) {

	free(p->state_end);
	freeLookaheadList(&p->lookaheads);
	freeKeywordList(&p->keywords);
	freeAutomaticMoveList(&p->autoMoves);
	freeActionList(&p->works);
	freeRuleList(&p->rules);

	freeString(&p->significantChars);

	memset(p, 0, sizeof(myGirlParser));
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
**  Realloc context list
**
**/
myContext* reallocContext(myContext* la, unsigned int newCapacity) {

	int* newAlloc = (int*)realloc(la->ints, sizeof(int) * (newCapacity + 1));
	if (newAlloc != NULL) {

		la->ints = newAlloc;
		la->capacity = newCapacity;
		return la;

	}
	else {

		perror("Erreur dans reallocContext");
		exit(EXIT_FAILURE);

	}

}


/**
 **  Push a context and change the state
 **/
void pushContext(myGirlParser* p, int chgState) {

	if (p->contexts.used == 0) {

		if (p->contexts.capacity < 2) {
			reallocContext(&p->contexts, 2);
		}
		memcpy(&p->contexts.ints[p->contexts.used], &p->currentState, sizeof(int));
		p->contexts.used = 1;

	}
	else if (p->contexts.used + 1 < p->contexts.capacity) {

		memcpy(&p->contexts.ints[p->contexts.used], &p->currentState, sizeof(int));
		p->contexts.used += 1;

	}
	else {

		reallocContext(&p->contexts, p->contexts.capacity + MINSIZE);
		memcpy(&p->contexts.ints[p->contexts.used], &p->currentState, sizeof(myKeyword));
		p->contexts.used += 1;

	}
    
    p->currentState = chgState;

}

int popContext(myGirlParser* p) {


	int val;
	if (p->contexts.used > 0) {

		val = p->contexts.ints[p->contexts.used - 1];
		for (int index = 1; index < p->contexts.used; ++index) {
			p->contexts.ints[index - 1] = p->contexts.ints[index];
		}
		--p->contexts.used;
		p->currentState = val;
		return val;
	} else {
		wprintf(L"no context available\n");
		exit(EXIT_FAILURE);
	}
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
 **  Libère la mémoire
 **  myLookahead : data
 **/
void freeLookahead(myLookahead* p) {

	free(p->state_for);
	free(p->if_c);
	p->countState = 0;
	p->countChars = 0;
	p->state_for = NULL;
	p->if_c = NULL;

}


/**
 **  Libère la mémoire
 **  myRule : data
**/
void freeRule(myRule* p) {

	free(p->states);
	p->countState = 0;
	freeString(&p->name);

}


/**
**  Libère la mémoire
**  myKeyword : data
**/
void freeKeyword(myKeyword* p) {

	free(p->state_for);
	for (int index = 0; index < p->countStrings; ++index) {
		freeString(&p->if_s[index]);
	}
	free(p->if_s);
	p->countState = 0;
	p->countStrings = 0;
	p->state_for = NULL;
	p->if_s = NULL;

}

/**
**  Libère la mémoire
**  myAutomaticMove : data
**/
void freeAutomaticMove(myAutomaticMove* p) {

	free(p->state_from);
	p->countState = 0;
	p->state_from = NULL;

}

/**
**  Libère la mémoire
**  myAction : data
**/
void freeAction(myAction* p) {

	free(p->states_at);
	free(p->functions);
	for (int index = 0; index < p->countFunctions; ++index) {
		freeString(&p->functionNames[index]);
	}
	free(p->functionNames);
	p->countState = 0;
	p->countFunctions = 0;
	p->states_at = NULL;
	p->functions = NULL;
	p->functionNames = NULL;

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
**  Create a rule
**
**/
myRule createRule(int* states_for, unsigned int countFor, wchar_t* name) {

	myRule h;

	h.states = (int*)malloc(sizeof(int) * countFor);
	h.countState = countFor;
	memcpy(h.states, states_for, countFor * sizeof(int));
	h.name = createString(MINSIZE);
	writeString(&h.name, name);

	return h;

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
    h.countStrings = countString;
    for(int index = 0; index < countString; ++index) {
        
        h.if_s[index] = createString(sList[index].used);
        writeString(&h.if_s[index], sList[index].strContent);
        
    }
    h.state_next = next;
    
    return h;
    
}

/**
 **  Realloc rule list
 **
 **/
myRuleList* reallocRule(myRuleList* la, unsigned int newCapacity) {
    
	myRule* newAlloc = (myRule*)realloc(la->list, sizeof(myRule) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        la->list = newAlloc;
        la->capacity = newCapacity;
        return la;
        
    } else {
        
        perror("Erreur dans reallocRule");
        exit(EXIT_FAILURE);
        
    }
    
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

	}
	else {

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
**   Ecrit dans la liste
**   indépendamment de la taille nécessaire
**   myKeywordList : list
**   myKeyword : object
**/
myRuleList* writeRule(myRuleList* m, myRule* la) {

	if (m->used == 0) {

		if (m->capacity < 2) {
			reallocRule(m, 2);
		}
		memcpy(&m->list[m->used], la, sizeof(myRule));
		m->used = 1;

	}
	else if (m->used + 1 < m->capacity) {

		memcpy(&m->list[m->used], la, sizeof(myRule));
		m->used += 1;

	}
	else {

		reallocRule(m, m->capacity + MINSIZE);
		memcpy(&m->list[m->used], la, sizeof(myRule));
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
**   Add rule
**
**/
void addRule(myGirlParser* girl, int* states_for, unsigned int countFor, wchar_t* name) {

	myRule h = createRule(states_for, countFor, name);
	writeRule(&girl->rules, &h);

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
myAction createAction(int* states_at, unsigned int countAt, myString* s, action* f, unsigned int countF) {
    
    myAction h;
    
    h.states_at = (int*)malloc(sizeof(int) * countAt);
    h.countState = countAt;
    memcpy(h.states_at, states_at, countAt * sizeof(int));
    h.functions = (action*)malloc(sizeof(action) * countF);
    h.countFunctions = countF;
	h.functionNames = (myString*)malloc(sizeof(myString) * countF);
	for (int index = 0; index < countF; ++index) {
        
        h.functions[index] = f[index];
		h.functionNames[index] = createString(s[index].used);
		writeString(&h.functionNames[index], s[index].strContent);

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
void addAction(myGirlParser* girl, int* states_at, unsigned int countAt, myString* s, action* f, unsigned int countF) {
    
    myAction h = createAction(states_at, countAt, s, f, countF);
    writeAction(&girl->works, &h);
    
}

/**
 **  Create a functional parser
 **
 **/
myFunctional createFunctional(int* states_at, unsigned int countAt, myString* s, interpret* f, unsigned int countF) {
    
    myFunctional h;
    
    h.states_at = (int*)malloc(sizeof(int) * countAt);
    h.countState = countAt;
    memcpy(h.states_at, states_at, countAt * sizeof(int));
    h.functionals = (interpret*)malloc(sizeof(interpret) * countF);
    h.countFunctions = countF;
    h.functionNames = (myString*)malloc(sizeof(myString) * countF);
    for (int index = 0; index < countF; ++index) {
        
        h.functionals[index] = f[index];
        h.functionNames[index] = createString(s[index].used);
        writeString(&h.functionNames[index], s[index].strContent);
        
    }
    
    return h;
    
}

/**
 **  Realloc functional list
 **
 **/
myFunctionalList* reallocFunctional(myFunctionalList* la, unsigned int newCapacity) {
    
    myFunctional* newAlloc = (myFunctional*)realloc(la->funs, sizeof(myFunctional) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        la->funs = newAlloc;
        la->capacity = newCapacity;
        return la;
        
    } else {
        
        perror("Erreur dans reallocFunctional");
        exit(EXIT_FAILURE);
        
    }
    
}

/**
 **   Ecrit dans la liste
 **   indépendamment de la taille nécessaire
 **   myFunctionalList : list
 **   myFunctional : object
 **/
myFunctionalList* writeFunctional(myFunctionalList* m, myFunctional* la) {
    
    if (m->used == 0) {
        
        if (m->capacity < 2) {
            reallocFunctional(m, 2);
        }
        memcpy(&m->funs[m->used], la, sizeof(myFunctional));
        m->used = 1;
        
    } else if (m->used + 1 < m->capacity) {
        
        memcpy(&m->funs[m->used], la, sizeof(myFunctional));
        m->used += 1;
        
    } else {
        
        reallocFunctional(m, m->capacity + MINSIZE);
        memcpy(&m->funs[m->used], la, sizeof(myFunctional));
        m->used += 1;
        
    }
    
    return m;
    
}


/**
 **   Add functional
 **
 **/
void addFunctional(myGirlParser* girl, int* states_at, unsigned int countAt, myString* s, interpret* f, unsigned int countF) {
    
    myFunctional h = createFunctional(states_at, countAt, s, f, countF);
    writeFunctional(&girl->functionals, &h);
    
}


/**
 **   Search a keyword
 **
 **/
bool searchKeyword(myGirlParser* p, int state, int* next) {

	bool found = false;
	unsigned int offIndex = p->reader->pos;
	for (int index = 0; index < p->keywords.used && !found; ++index) {

		myKeyword* l = &p->keywords.keys[index];
		for (int stateIndex = 0; stateIndex < l->countState && !found; ++stateIndex) {

			if (l->state_for[stateIndex] == state) {

				for (int stringIndex = 0; stringIndex < l->countStrings && !found; ++stringIndex) {

                    if (!yieldnReadInMemory(p->reader, l->if_s[stringIndex].used)) return false;
					if (wcsncmp(p->reader->line.strContent + p->reader->pos, l->if_s[stringIndex].strContent, l->if_s[stringIndex].used) == 0) {
						p->reader->pos += l->if_s[stringIndex].used;
						found = true;
						*next = l->state_next;
					}

				}

			}

		}

	}

	/** keyword must not be followed by one another significant chars **/
	if (found) {

        if (!yieldnReadInMemory(p->reader, 1)) return false;
		while (found && wcschr(p->significantChars.strContent, *(p->reader->line.strContent + p->reader->pos))) {
            ++p->reader->pos;
			found = false;
		}

	}

	if (!found)
        p->reader->pos = offIndex;

	return found;

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
                    
                    if (!yieldnReadOut(p->reader, 1)) return false;
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
bool searchAction(myGirlParser* p, int state, myString* textfunction, action** f, unsigned int* countFunctions) {
    
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
					writeString(textfunction, l->functionNames[index].strContent);
                    
                }

            }
        }
        
    }
    
    return found;
    
}

/**
 **  Search functionals and execute them
 **/
bool searchFunctional(myGirlParser* p, int state, myString* textfunction, interpret** f, unsigned int* countFunctions) {
    
    bool found = false;
    for(int index = 0; index < p->functionals.used && !found; ++index) {
        
        myFunctional* l = &p->functionals.funs[index];
        for(int stateIndex = 0; stateIndex < l->countState && !found; ++stateIndex) {
            
            if (l->states_at[stateIndex] == state) {
                
                found = true;
                *f = (interpret*)malloc(sizeof(interpret) * l->countFunctions);
                *countFunctions = l->countFunctions;
                for(int index = 0; index < *countFunctions; ++index) {
                    
                    (*f)[index] = l->functionals[index];
                    if (index > 0)
                        writeString(textfunction, L",");
                    writeString(textfunction, l->functionNames[index].strContent);
                    
                }
                
            }
        }
        
    }
    
    return found;
    
}


/**
 **   processus logique d'analyse
 **/
bool processLogical(myGirlParser* p, void* object) {
    
    int next;
    
    /** functional **/
    interpret* u = NULL;
    unsigned int ucount;
    myString usnf = createString(0);
    if (searchFunctional(p, p->currentState, &usnf, &u, &ucount)) {
        
        interpret* ucurrent = u;
        for(int ucountF = 0; ucountF < ucount; ++ucountF, ++ucurrent) {
            
            createExInterpret(p, *ucurrent);
            
        }
        free(u);
        
    }
    freeString(&usnf);
    
    
    /** lookahead **/
    if (!yieldnReadOut(p->reader, 1)) return false;
    if (searchLookahead(p, p->currentState, *(p->reader->line.strContent + p->reader->pos), &next)) {
        
        /** avancer le pointeur (si je mange) **/
        ++p->reader->pos;
        /** changement d'état **/
        p->currentState = next;
        return true;
        
    }
    
    /** Keywords **/
    if (searchKeyword(p, p->currentState, &next)) {
        
        /** changement d'état **/
        p->currentState = next;
        return true;
        
    }
    
    /** launch actions **/
    action* a = NULL;
    unsigned int count;
    myString snf = createString(0);
    if (searchAction(p, p->currentState, &snf, &a, &count)) {
        
        action* current = a;
        for(int countF = 0; countF < count; ++countF, ++current) {
            
            (*current)(p, object);
            
        }
        free(a);
    }
    freeString(&snf);
    
    /** automatic moves **/
    if (searchAutomaticMove(p, p->currentState, &next)) {
        
        /** changement d'état **/
        p->currentState = next;
        return true;
        
    }
    
    for(int endIndex = 0; endIndex < p->countState; ++endIndex) {
        
        if (p->state_end[endIndex] == p->currentState) {
            
            p->notAvailable = true;
            
        }
        
    }
    
    return true;

}

bool yieldprocess(myGirlParser* p, void* object) {
    
    while(yieldRead(p->reader) && !p->notAvailable && processLogical(p, object));
    
    return p->notAvailable;
}


bool process(myGirlParser* p, void* object) {

    while(p->reader->pos < p->reader->line.used && !p->notAvailable && processLogical(p, object));

	return p->notAvailable;
}


/**
**
**  Dump lookahead definition
**/
void dumpLookahead(myLookahead* p) {

	wprintf(L"  For state = [");
	for (int index = 0; index < p->countState; ++index) {

		if (index > 0)
			wprintf(L",");
		wprintf(L"%d", p->state_for[index]);
	}
	wprintf(L"]\n");
	wprintf(L"  Lookaheads = [");
	for (int index = 0; index < p->countChars; ++index) {

		if (index > 0)
			wprintf(L",");
		wprintf(L"%lc", p->if_c[index]);

	}
	wprintf(L"]\n");
	wprintf(L"  Next state = %d\n", p->state_next);
}


/**
**
**  Dump keyword definition
**/
void dumpKeyword(myKeyword* p) {

	wprintf(L"  For state = [");
	for (int index = 0; index < p->countState; ++index) {

		if (index > 0)
			wprintf(L",");
		wprintf(L"%d", p->state_for[index]);
	}
	wprintf(L"]\n");
	wprintf(L"  Keywords = [");
	for (int index = 0; index < p->countStrings; ++index) {

		if (index > 0)
			wprintf(L",");
		wprintf(L"%ls", p->if_s[index].strContent);

	}
	wprintf(L"]\n");
	wprintf(L"  Next state = %d\n", p->state_next);
}


/**
 **
 **  Dump girl parser definition
 **/
void dumpGirlParser(myGirlParser* p) {


	wprintf(L"Start state = %d\n", p->state_start);
	wprintf(L"End state = [");
	for (int index = 0; index < p->countState; ++index) {

		if (index > 0)
			wprintf(L",");
		wprintf(L"%d", p->state_end[index]);
	}
	wprintf(L"]\n");
	wprintf(L"Current state = %d\n", p->currentState);
	wprintf(L"Current input = '%ls'\n", p->reader->line.strContent);
	wprintf(L"Current position into input = '%d'\n", p->reader->pos);

	wprintf(L"List(keyword) = {\n");
	for (int index = 0; index < p->keywords.used; ++index) {

		if (index > 0)
			wprintf(L",\n");
		dumpKeyword(&p->keywords.keys[index]);

	}
	wprintf(L"}\n");

	wprintf(L"List(lookahead) = {\n");
	for (int index = 0; index < p->lookaheads.used; ++index) {

		if (index > 0)
			wprintf(L",\n");
		dumpLookahead(&p->lookaheads.list[index]);

	}
	wprintf(L"}\n");
}



