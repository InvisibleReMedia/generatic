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
 **  Surround a sequence by left and right
 **/
bool surround(myYieldReadPart* y, myString left, interpret f, myString right, myValueKeyList* l) {

	bool c = true;
    if (!yieldnRead(y, left.used)) return false;
	if (wcsncmp(y->line.strContent + y->pos, left.strContent, left.used) == 0) {
        y->pos += left.used;
		c &= f(y, l);
        if (!yieldnRead(y, right.used)) return false;
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
bool loop(myYieldReadPart* y, myString left, interpret f, myString interval, myString right, myValueKeyList* l) {

	bool c = false;
	int index = 0;
    
    if (!yieldnRead(y, left.used)) return false;
	if (wcsncmp(y->line.strContent + y->pos, left.strContent, left.used) == 0) {
        y->pos += left.used;
        c = true;
		do {
            if (!yieldnRead(y, interval.used)) return false;
			if (index > 0 && wcsncmp(y->line.strContent + y->pos, interval.strContent, interval.used) == 0) {
                y->pos += interval.used;
			}
			c &= f(y, l);
            if (!yieldnRead(y, right.used)) return false;
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
bool or(myYieldReadPart* y, interpret left, interpret right, myValueKeyList* l) {

	return left(y, l) || right(y, l);
}

/**
 **   selection type
 **/
bool type(myYieldReadPart* y, interpret f, myString typeName, myValueKeyList* l) {

	writeValueKey(l, typeName.strContent, L"");
	return f(y, l);
}

/**
 **  expression [from-to]*
 **/
bool expression_ident(myYieldReadPart* y, wchar_t from, wchar_t to, myValueKeyList* l) {

    if (!yieldnRead(y, 1)) return false;
    while (y->line.strContent[y->pos] >= from && y->line.strContent[y->pos] < to) {

		wchar_t c[2];

		c[0] = y->line.strContent[y->pos];
		c[1] = L'\0';
		writeString(&l->element[l->used - 1].value, c);
        ++y->pos;
        if (!yieldnRead(y, 1)) return false;
	}
	return true;

}

/**
 **    count any number of elements
 **/
bool expression_size(myYieldReadPart* y, int count, myValueKeyList* l) {

	for (int counter = 0; counter < count; ++counter) {

		wchar_t c[2];

        if (!yieldnRead(y, 1)) return false;
		c[0] = y->line.strContent[y->pos];
		c[1] = L'\0';
		writeString(&l->element[l->used - 1].value, c);
        ++y->pos;

	}
    
    return true;

}

/**
 **    Compare an expression with a test string
 **/
bool expression_cmp(myYieldReadPart* y, myString test, myValueKeyList* l) {

    if (!yieldnRead(y, test.used)) return false;
	return wcsncmp(y->line.strContent + y->pos, test.strContent, test.used) == 0;

}


/**
 **  create an exInterpreter
 **  it is a sequence of nested functions calls that returns a list of name/value elements found
 **  to select a name for any value, use type() function
 **/
myValueKeyList createExInterpret(myYieldReadPart* y, interpret f) {

	myValueKeyList list = createValueKeyList(0);

	f(y, &list);
	return list;

}


