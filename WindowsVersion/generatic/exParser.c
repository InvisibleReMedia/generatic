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
#include "girlParser.h"
#include "exParser.h"



bool readExParser(myString* source, myGirlParser* p, myGirlParser* dest) {



}


bool funMoveCursor(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	++ptrParser->currentIndex;
}

bool funAddSignificantChars(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	wchar_t copy[2];
	copy[0] = ptrParser->input.strContent[ptrParser->currentIndex];
	++ptrParser->currentIndex;
	copy[1] = L'\0';
	writeString(&ptrDest->significantChars, copy);

}


bool funAddStartState(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	wchar_t c = ptrParser->input.strContent[ptrParser->currentIndex];
	if (c >= L'0' && c <= L'9') {
		int i = wtoi(c);
		if (ptrDest->state_start <= 0xFFF6) {
			ptrDest->state_start *= 10;
			ptrDest->state_start += i;
		}
		++ptrParser->currentIndex;
	}
	else {
		/** end number sequence : back to the first state **/
		ptrParser->currentState = 1;
	}


}

bool funInitEndState(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	ptrDest->countState = 0;
	ptrDest->state_end = (int*)malloc(sizeof(int) * (ptrDest->countState + 1));
	if (ptrDest->state_end == NULL) {
		perror("Error in funInitEndState:");
		exit(EXIT_FAILURE);
	}
	ptrDest->state_end[ptrDest->countState] = 0;

}

bool funNewEndState(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	int* newPtr = (int*)realloc(ptrDest->state_end, sizeof(int) * (ptrDest->countState + 1));
	if (newPtr == NULL) {
		perror("Error in funNewEndState:");
		exit(EXIT_FAILURE);
	}
	ptrDest->state_end = newPtr;
	++ptrDest->countState;
	ptrDest->state_end[ptrDest->countState] = 0;

}


bool funAddEndState(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	wchar_t c = ptrParser->input.strContent[ptrParser->currentIndex];
	++ptrParser->currentIndex;
	if (c >= L'0' && c <= L'9') {
		int i = wtoi(c);
		if (ptrDest->state_end[ptrDest->countState] <= 0xFFF6) {
			ptrDest->state_end[ptrDest->countState] *= 10;
			ptrDest->state_end[ptrDest->countState] += i;
		}
	}
	else if (c == L',') {
		funNewEndState(a, b);
	}
	else if (c == L']') {
		/** end number sequence : back to the first state **/
		ptrParser->currentState = 1;
	}


}


bool funInitRuleName(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	ptrDest->currentRule = createRule(setIntList(0), 0, L"");

}




bool funAddRuleName(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	wchar_t c = ptrParser->input.strContent[ptrParser->currentIndex];
	++ptrParser->currentIndex;
	if (wcschr(ptrParser->significantChars.strContent, c)) {
		writeString(&ptrDest->currentRule.name, c);
	} else if (c == L'[') {
		/** end rule name sequence : next state **/
		ptrDest->currentRule.countState = 0;
		ptrParser->currentState = 14;
	}

}


bool funNewRuleState(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	int* newPtr = (int*)realloc(ptrDest->currentRule.states, sizeof(int) * (ptrDest->currentRule.countState + 1));
	if (newPtr == NULL) {
		perror("Error in funNewEndState:");
		exit(EXIT_FAILURE);
	}
	ptrDest->state_end = newPtr;
	++ptrDest->currentRule.countState;
	ptrDest->state_end[ptrDest->currentRule.countState] = 0;

}


bool funAddRuleState(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	wchar_t c = ptrParser->input.strContent[ptrParser->currentIndex];
	++ptrParser->currentIndex;
	if (c >= L'0' && c <= L'9') {
		int i = wtoi(c);
		if (ptrDest->currentRule.states[ptrDest->currentRule.countState] <= 0xFFF6) {
			ptrDest->currentRule.states[ptrDest->currentRule.countState] *= 10;
			ptrDest->currentRule.states[ptrDest->currentRule.countState] += i;
		}
	}
	else if (c == L',') {
		funNewRuleState(a, b);
	}
	else if (c == L']') {
		/** end the list **/
		/** end number sequence : next state **/
		ptrParser->currentState = 15;
		writeRule(&ptrDest->rules, &ptrDest->currentRule);
	}


}


bool funPushContextRule(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	pushContext(ptrParser);
	ptrParser->currentState = 18;

}

bool funPushContextKeyword(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	pushContext(ptrParser);
	ptrParser->currentState = 24;

}

bool funPushContextLookahead(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	pushContext(ptrParser);
	ptrParser->currentState = 18;

}

bool funPushContextAction(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	pushContext(ptrParser);
	ptrParser->currentState = 18;

}

bool funPushContextAuto(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	pushContext(ptrParser);
	ptrParser->currentState = 18;

}


bool funInitKeyword(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	ptrDest->currentKeyword = createKeyword(setIntList(0), 0, setStringList(0), 0, 0);

}




bool funAddKeyword(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myGirlParser* ptrDest = (myGirlParser*)b;

	wchar_t c = ptrParser->input.strContent[ptrParser->currentIndex];
	++ptrParser->currentIndex;
	if (c == '"') {

	}
	if (wcschr(ptrParser->significantChars.strContent, c)) {
		writeString(&ptrDest->currentRule.name, c);
	}
	else if (c == L'[') {
		/** end rule name sequence : next state **/
		ptrDest->currentRule.countState = 0;
		ptrParser->currentState = 14;
	}

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
	/** any ; char **/
	addLookahead(&reader, setIntList(1, 1), 1, setCharList(1, L';'), 1, 1);

	/** comment identifier **/
	addLookahead(&reader, setIntList(1, 1), 1, setCharList(1, L'#'), 1, 2);
	addLookahead(&reader, setIntList(1, 2), 1, setCharList(1, L'\n'), 1, 1);
	addAction(&reader, setIntList(1, 2), 1, setStringList(1, L"funMoveCursor"), setActionList(1, funMoveCursor), 1);

	/** first line : significantChars = "..." **/
	addKeyword(&reader, setIntList(1, 1), 1, setStringList(1, L"significantChars"), 1, 3);
	addLookahead(&reader, setIntList(1, 3), 1, setCharList(2, L' ', L'\t'), 2, 3);
	addLookahead(&reader, setIntList(1, 3), 1, setCharList(2, L'='), 1, 4);
	addLookahead(&reader, setIntList(1, 4), 1, setCharList(2, L' ', L'\t'), 2, 4);
	addLookahead(&reader, setIntList(1, 4), 1, setCharList(2, L'"'), 1, 5);
	addLookahead(&reader, setIntList(1, 5), 1, setCharList(2, L'"'), 1, 1);
	addAction(&reader, setIntList(1, 5), 1, setStringList(1, L"funAddSignificantChars"), setActionList(1, funAddSignificantChars), 5);

	/** second line : start state = NUMBER **/
	addKeyword(&reader, setIntList(1, 1), 1, setStringList(1, L"start"), 1, 6);
	addLookahead(&reader, setIntList(1, 6), 1, setCharList(2, L' ', L'\t'), 2, 6);
	addKeyword(&reader, setIntList(1, 6), 1, setStringList(1, L"state"), 1, 7);
	addLookahead(&reader, setIntList(1, 7), 1, setCharList(2, L' ', L'\t'), 2, 7);
	addLookahead(&reader, setIntList(1, 7), 1, setCharList(2, L'='), 1, 8);
	addAction(&reader, setIntList(1, 8), 1, setStringList(1, L"funAddStartState"), setActionList(1, funAddStartState), 1);

	/** third line : end state = [NUMBER,..] **/
	addKeyword(&reader, setIntList(1, 1), 1, setStringList(1, L"end"), 1, 9);
	addLookahead(&reader, setIntList(1, 9), 1, setCharList(2, L' ', L'\t'), 2, 9);
	addKeyword(&reader, setIntList(1, 9), 1, setStringList(1, L"state"), 1, 10);
	addLookahead(&reader, setIntList(1, 10), 1, setCharList(2, L' ', L'\t'), 2, 10);
	addLookahead(&reader, setIntList(1, 10), 1, setCharList(2, L'='), 1, 11);
	addLookahead(&reader, setIntList(1, 11), 1, setCharList(2, L' ', L'\t'), 2, 11);
	addAction(&reader, setIntList(1, 11), 1, setStringList(1, L"funInitEndState"), setActionList(1, funInitEndState), 1);
	addLookahead(&reader, setIntList(1, 11), 1, setCharList(2, L'['), 1, 12);
	addLookahead(&reader, setIntList(1, 12), 1, setCharList(2, L' ', L'\t'), 2, 12);
	addAction(&reader, setIntList(1, 12), 1, setStringList(1, L"funAddEndState"), setActionList(1, funAddEndState), 1);

	/** start grammar rule name[...] **/
	addAction(&reader, setIntList(1, 1), 1, setStringList(1, L"funInitRuleName"), setActionList(1, funInitRuleName), 1);
	addAutomaticMove(&reader, setIntList(1, 1), 1, 13);
	addAction(&reader, setIntList(1, 13), 1, setStringList(1, L"funAddRuleName"), setActionList(1, funAddRuleName), 1);
	/** start NUMBER list (as previous) **/
	addLookahead(&reader, setIntList(1, 14), 1, setCharList(2, L' ', L'\t'), 2, 14);
	addAction(&reader, setIntList(1, 14), 1, setStringList(1, L"funAddRuleState"), setActionList(1, funAddRuleState), 1);
	/** syntax **/
	addLookahead(&reader, setIntList(1, 15), 1, setCharList(3, L' ', L'\t', L'\n'), 3, 15);
	addLookahead(&reader, setIntList(1, 15), 1, setCharList(1, L'='), 1, 16);
	addLookahead(&reader, setIntList(1, 16), 1, setCharList(3, L' ', L'\t', L'\n'), 3, 16);
	addLookahead(&reader, setIntList(1, 16), 1, setCharList(1, L'{'), 1, 17);
	addLookahead(&reader, setIntList(1, 17), 1, setCharList(3, L' ', L'\t', L'\n'), 3, 17);
	addLookahead(&reader, setIntList(1, 17), 1, setCharList(1, L'{'), 1, 18);
	/** start a new context **/
	addAction(&reader, setIntList(1, 17), 1, setStringList(1, "funPushContextRule"), setActionList(1, funPushContextRule), 1);

	addLookahead(&reader, setIntList(1, 18), 1, setCharList(3, L' ', L'\t', L'\n'), 3, 18);
	/** start keywords **/
	addKeyword(&reader, setIntList(1, 18), 1, setStringList(1, "keywords"), 1, 19);
	addKeyword(&reader, setIntList(1, 18), 1, setStringList(1, "or"), 1, 20);
	addKeyword(&reader, setIntList(1, 18), 1, setStringList(1, "and"), 1, 21);

	/** keywords content **/
	addLookahead(&reader, setIntList(1, 19), 1, setCharList(3, L' ', L'\t', L'\n'), 3, 19);
	addLookahead(&reader, setIntList(1, 19), 1, setCharList(1, L'='), 1, 22);
	addLookahead(&reader, setIntList(1, 22), 1, setCharList(3, L' ', L'\t', L'\n'), 3, 22);
	addLookahead(&reader, setIntList(1, 22), 1, setCharList(1, L'{'), 1, 23);
	/** start a new context **/
	addAction(&reader, setIntList(1, 23), 1, setStringList(1, "funPushContextKeyword"), setActionList(1, funPushContextKeyword), 1);

	addLookahead(&reader, setIntList(1, 24), 1, setCharList(3, L' ', L'\t', L'\n'), 3, 24);
	addKeyword(&reader, setIntList(1, 24), 1, setStringList(1, "for"), 1, 24);
	addLookahead(&reader, setIntList(1, 24), 1, setCharList(2, L'['), 1, 25);
	addAction(&reader, setIntList(1, 25), 1, setStringList(1, L"funInitKeyword"), setActionList(1, funInitKeyword), 1);
	addLookahead(&reader, setIntList(1, 25), 1, setCharList(3, L' ', L'\t', L'\n'), 3, 25);
	addAutomaticMove(&reader, setIntList(1, 25), 1, 26);
	addLookahead(&reader, setIntList(1, 26), 1, setCharList(3, L' ', L'\t', L'\n'), 3, 26);
	addAction(&reader, setIntList(1, 26), 1, setStringList(1, L"funAddKeyword"), setActionList(1, funAddKeyword), 1);


	/** read with a non dos format for new lines **/
	readFromFile(fileName, readExParser, &reader, &newDest);
}
