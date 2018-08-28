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
#include "PowerShell/fileSystem.h"
#include <stdarg.h>
#include "exInterpret.h"
#include "girlParser.h"
#include "exParser.h"



bool readExParser(myYieldReadPart* y, void* p, void* dest) {

    myGirlParser* ptrParser = (myGirlParser*)p;
    ptrParser->reader = y;

    return !yieldprocess(p, dest);

}


bool funMoveCursor(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
    if (!yieldnReadOut(ptrParser->reader, 1)) return false;
    ++ptrParser->reader->pos;
    return true;
}

bool funAddSignificantChars(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	wchar_t copy[2];
    if (!yieldnReadOut(ptrParser->reader, 1)) return false;
    copy[0] = ptrParser->reader->line.strContent[ptrParser->reader->pos];
    ++ptrParser->reader->pos;
	copy[1] = L'\0';
	writeString(&ptrDest->significantChars, copy);

    return true;
}


bool funAddStartState(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

    if (!yieldnReadOut(ptrParser->reader, 1)) return false;
	wchar_t c = ptrParser->reader->line.strContent[ptrParser->reader->pos];
	if (c >= L'0' && c <= L'9') {
        int i = (int)(c - L'0');
		if (ptrDest->state_start <= 0xFFF6) {
			ptrDest->state_start *= 10;
			ptrDest->state_start += i;
		}
        ++ptrParser->reader->pos;
	}
	else {
		/** end number sequence : back to the first state **/
		ptrParser->currentState = 1;
	}

    return true;
}

/**
 **
 **    Load a file text source for a girlParser
 **
 **/
myGirlParser loadExParserFromFile(char* fileName) {

	myString s = createString(0);
	writeString(&s, L"abcdefghiljklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_");
	myGirlParser reader = createGirlParser(1, setIntList(1, 2), 1, s);

	myGirlParser newDest = createGirlParser(1, setIntList(0), 0, s);

	/** any new line chars **/
	addLookahead(&reader, setIntList(1, 1), 1, setCharList(1, L'\n'), 1, 1);

	/** comment identifier **/
    addLookahead(&reader, setIntList(1, 1), 1, setCharList(1, L';'), 1, 2);
	addLookahead(&reader, setIntList(1, 2), 1, setCharList(1, L'\n'), 1, 1);
	addAction(&reader, setIntList(1, 2), 1, setStringList(1, L"funMoveCursor"), setActionList(1, funMoveCursor), 1);

	/** first line : significantChars = "..." **/
	addKeyword(&reader, setIntList(1, 1), 1, setStringList(1, L"significantChars"), 1, 3);
	addLookahead(&reader, setIntList(1, 3), 1, setCharList(2, L' ', L'\t'), 2, 3);
	addLookahead(&reader, setIntList(1, 3), 1, setCharList(2, L'='), 1, 4);
	addLookahead(&reader, setIntList(1, 4), 1, setCharList(2, L' ', L'\t'), 2, 4);
	addLookahead(&reader, setIntList(1, 4), 1, setCharList(2, L'"'), 1, 5);
	addLookahead(&reader, setIntList(1, 5), 1, setCharList(2, L'"'), 1, 1);
	addAction(&reader, setIntList(1, 5), 1, setStringList(1, L"funAddSignificantChars"), setActionList(1, funAddSignificantChars), 1);

	/** second line : start state = NUMBER **/
	addKeyword(&reader, setIntList(1, 1), 1, setStringList(1, L"start"), 1, 6);
	addLookahead(&reader, setIntList(1, 6), 1, setCharList(2, L' ', L'\t'), 2, 6);
	addKeyword(&reader, setIntList(1, 6), 1, setStringList(1, L"state"), 1, 7);
	addLookahead(&reader, setIntList(1, 7), 1, setCharList(2, L' ', L'\t'), 2, 7);
	addLookahead(&reader, setIntList(1, 7), 1, setCharList(2, L'='), 1, 8);
	addAction(&reader, setIntList(1, 8), 1, setStringList(1, L"funAddStartState"), setActionList(1, funAddStartState), 1);

	/** read with a non dos format for new lines **/
	yieldReadFromFile(fileName, readExParser, &reader, &newDest);
    
    return newDest;
}
