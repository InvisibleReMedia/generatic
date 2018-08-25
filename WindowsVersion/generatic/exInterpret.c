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
#include "girlParser.h"
#include "exInterpret.h"



bool surround(myString input, unsigned int current, myString left, interpret f, myString right, myValueKeyList* l) {

	bool c = true;
	if (wcsncmp(input.strContent + current, left.strContent, left.used) == 0) {
		++current;
		c &= f(input, current, l);
		if (wcsncmp(input.strContent + current, left.strContent, left.used) == 0) {
			++current;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool loop(myString input, unsigned int current, myString left, interpret f, myString interval, myString right, myValueKeyList* l) {

	bool c = true;
	int index = 0;
	if (wcsncmp(input.strContent + current, left.strContent, left.used) == 0) {
		++current;
		do {
			if (index > 0 && wcsncmp(input.strContent + current, interval.strContent, interval.used) == 0) {
				++current;
			}
			c &= f(input, current, l);
			if (wcsncmp(input.strContent + current, right.strContent, right.used) == 0) {
				++current;
				break;
			}
			else
				++index;
		} while (true);
	}
	else
		return false;
}


bool or(myString input, unsigned int current, interpret left, interpret right, myValueKeyList* l) {

	return left(input, current, l) || right(input, current, l);
}

bool type(myString input, unsigned int current, interpret f, myString typeName, myValueKeyList* l) {

	writeValueKey(l, typeName.strContent, L"");
	return f(input, current, l);
}

bool expression_ident(myString input, unsigned int current, wchar_t from, wchar_t to, myValueKeyList* l) {

	while (input.strContent[current] >= from && input.strContent[current] < to) {

		wchar_t c[2];

		c[0] = input.strContent[current];
		c[1] = L'\0';
		writeString(&l->element[l->used - 1].value, c);
		++current;
	}
	return true;

}

bool expression_size(myString input, unsigned int current, int count, myValueKeyList* l) {

	for (int counter = 0; counter < count; ++counter) {

		wchar_t c[2];

		c[0] = input.strContent[current];
		c[1] = L'\0';
		writeString(&l->element[l->used - 1].value, c);
		++current;

	}

}

bool expression_cmp(myString input, unsigned int current, myString test, myValueKeyList* l) {

	return wcsncmp(input.strContent + current, test.strContent, test.used) == 0;

}


myValueKeyList createExInterpret(myString input, interpret f) {

	myValueKeyList list = createValueKeyList(0);

	f(input, 0, &list);
	return list;

}