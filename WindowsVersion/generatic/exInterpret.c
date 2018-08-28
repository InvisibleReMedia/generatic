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
#include <stdarg.h>
#include "Unix/fileSystem.h"
#include "exInterpret.h"
#include "girlParser.h"


/**
 **  Changement de contexte
 **/
bool contextChange(void* a, int c) {
    
    myGirlParser* p = (myGirlParser*)a;
    pushContext(p, c);
    return true;
}

/**
 **  Surround a sequence by left and right
 **/
bool surround(void* a, myString left, interpret f, myString right, myValueKeyList* l) {

    myGirlParser* p = (myGirlParser*)a;
    myYieldReadPart* y = p->reader;
    
	bool c = true;
    if (!yieldnReadOut(y, left.used)) return false;
	if (wcsncmp(y->line.strContent + y->pos, left.strContent, left.used) == 0) {
        y->pos += left.used;
		c &= f(y, l);
        if (!yieldnReadOut(y, right.used)) return false;
		if (wcsncmp(y->line.strContent + y->pos, right.strContent, right.used) == 0) {
            y->pos += right.used;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

/**
 **  Repeat a sequence; start and end
 **/
bool loop(void* a, myString left, interpret f, myString interval, myString right, myValueKeyList* l) {

    myGirlParser* p = (myGirlParser*)a;
    myYieldReadPart* y = p->reader;
    
	bool c = false;
	int index = 0;
    
    if (!yieldnReadOut(y, left.used)) return false;
	if (wcsncmp(y->line.strContent + y->pos, left.strContent, left.used) == 0) {
        y->pos += left.used;
        c = true;
		do {
            if (!yieldnReadOut(y, interval.used)) return false;
			if (index > 0 && wcsncmp(y->line.strContent + y->pos, interval.strContent, interval.used) == 0) {
                y->pos += interval.used;
			}
			c &= f(y, l);
            if (!yieldnReadOut(y, right.used)) return false;
			if (wcsncmp(y->line.strContent + y->pos, right.strContent, right.used) == 0) {
                y->pos += right.used;
				break;
			}
			else
				++index;
		} while (true);
	}
    
    return c;
}


/**
 **   Or function : do one of them
 **
 **/
bool or(void* a, interpret left, interpret right, myValueKeyList* l) {

    myGirlParser* p = (myGirlParser*)a;
	return left(p, l) || right(p, l);
}

/**
 **   Or function : do one of them
 **
 **/
bool and(void* a, interpret left, interpret right, myValueKeyList* l) {
    
    myGirlParser* p = (myGirlParser*)a;
    bool res = left(p, l);
    res &= right(p, l);
    return res;
}

/**
 **   selection type
 **/
bool type(void* a, interpret f, myString typeName, myValueKeyList* l) {

    myGirlParser* p = (myGirlParser*)a;
	writeValueKey(l, typeName.strContent, L"");
	return f(p, l);
}

/**
 **  expression [from-to]*
 **/
bool expression_ident(void* a, wchar_t from, wchar_t to, myValueKeyList* l) {

    myGirlParser* p = (myGirlParser*)a;
    myYieldReadPart* y = p->reader;
    
    if (!yieldnReadOut(y, 1)) return false;
    while (y->line.strContent[y->pos] >= from && y->line.strContent[y->pos] < to) {

		wchar_t c[2];

		c[0] = y->line.strContent[y->pos];
		c[1] = L'\0';
		writeString(&l->element[l->used - 1].value, c);
        ++y->pos;
        if (!yieldnReadOut(y, 1)) return false;
	}
	return true;

}

/**
 **    count any number of elements
 **/
bool expression_size(void* a, int count, myValueKeyList* l) {

    myGirlParser* p = (myGirlParser*)a;
    myYieldReadPart* y = p->reader;
	for (int counter = 0; counter < count; ++counter) {

		wchar_t c[2];

        if (!yieldnReadOut(y, 1)) return false;
		c[0] = y->line.strContent[y->pos];
		c[1] = L'\0';
		writeString(&l->element[l->used - 1].value, c);
        ++y->pos;

	}
    
    return true;

}

/**
 **    search * but not in chars
 **/
bool expression_notin(void* a, wchar_t* chars, unsigned int count, myValueKeyList* l) {
    
    myGirlParser* p = (myGirlParser*)a;
    myYieldReadPart* y = p->reader;
    bool finished = false;
    while(!finished) {
        
        wchar_t c[2];
        
        if (!yieldnReadOut(y, 1)) return true;
        c[0] = y->line.strContent[y->pos];
        c[1] = L'\0';
        for(int index = 0; index < count; ++index) {
            
            if (chars[index] == c[0]) {
                finished = true;
                break;
            }
            
        }
        if (!finished) {
            writeString(&l->element[l->used - 1].value, c);
            ++y->pos;
        }

    }
    
    return finished;

}

/**
 **    search in chars
 **/
bool expression_in(void* a, wchar_t* chars, unsigned int count, myValueKeyList* l) {
    
    myGirlParser* p = (myGirlParser*)a;
    myYieldReadPart* y = p->reader;
    bool finished = false;
    while(!finished) {
        
        wchar_t c[2];
        
        if (!yieldnReadOut(y, 1)) return true;
        c[0] = y->line.strContent[y->pos];
        c[1] = L'\0';
        bool found = false;
        for(int index = 0; index < count; ++index) {
            
            if (chars[index] == c[0]) {
                found = true;
                break;
            }
            
        }
        if (found) {
            writeString(&l->element[l->used - 1].value, c);
            ++y->pos;
        } else {
            finished = true;
        }
        
    }
    
    return finished;
    
}

/**
 **    Compare an expression with a test string
 **/
bool expression_cmp(void* a, myString test, myValueKeyList* l) {

    myGirlParser* p = (myGirlParser*)a;
    myYieldReadPart* y = p->reader;
    if (!yieldnReadOut(y, test.used)) return false;
	return wcsncmp(y->line.strContent + y->pos, test.strContent, test.used) == 0;

}


/**
 **  create an exInterpreter
 **  it is a sequence of nested functions calls that returns a list of name/value elements found
 **  to select a name for any value, use type() function
 **/
myValueKeyList createExInterpret(void* a, interpret f) {

	myValueKeyList list = createValueKeyList(0);

	f(a, &list);
	return list;

}


