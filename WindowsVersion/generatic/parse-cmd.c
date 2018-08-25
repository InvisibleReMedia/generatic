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
#include "csv-reader.h"
#include "installing.h"
#include "parse-cmd.h"
#include <stdarg.h>
#include "girlParser.h"

/**
 **  Write string and empty src, udpate state and afterSpace
 **
 **/
void writeName(myString* name, myString* src, int* state, bool* afterSpace) {
    
    writeString(name, src->strContent);
    clearString(src);
    *state = 1;
    *afterSpace = true;
    
}

/**
 **  Write option and empty src, udpate state and afterSpace
 **
 **/
void writeOption(myString* option, myString* src, int* state, bool* afterSpace) {
    
    writeString(option, src->strContent);
    clearString(src);
    *state = 2;
    *afterSpace = true;
    
}

/**
 **  Write parameter into command and empty src, udpate state and afterSpace
 **
 **/
void writeParameter(myCommand* result, myString* src, int* state, bool* afterSpace) {
    
    myCommand cmd = createCommand();
    writeString(&cmd.value, src->strContent);
    writeCommand(&result->parameters, &cmd);
    clearString(src);
    *afterSpace = true;

}


/**
 **  Parse a command
 **/
bool parseCommand(myString s, myCommand* result) {
        
    wchar_t input[2];
    input[1] = L'\0';
    int pos = 0;
    wchar_t c;
    int state = 0;
    bool afterSpace = true;
    myString value = createString(MINSIZE);

    while(nonDosFormatString(s, &c, &pos)) {
        
        if (c == L'\n' || ((c == L' ' || c == L'\t') && (state >= 0 && state < 2)) || (c == L',' && state > 1)) {
            
            if (!afterSpace) {
                
                if (state == 0) {
                    
                    writeName(&result->name, &value, &state, &afterSpace);

                } else if (state == 1) {
                    
                    writeOption(&result->option, &value, &state, &afterSpace);

                } else {

                    /** recherche de commande dans le fichier csv **/
                    writeParameter(result, &value, &state, &afterSpace);

                }

            }
            
        } else {
            
            afterSpace = false;
            input[0] = c;
            writeString(&value, input);
            
        }
        
    }
    
    /** possible ? **/
    if (value.used > 0) {
        
        if (state == 0) {
            
            writeName(&result->name, &value, &state, &afterSpace);
            
        } else if (state == 1) {
            
            writeOption(&result->option, &value, &state, &afterSpace);
            
        } else {
            
            writeParameter(result, &value, &state, &afterSpace);
            
        }

    }
    
    freeString(&value);
    
    return state > 0;
}


/**
 **
 **   add name
 **/
bool funAddName(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myCommand* ptrCmd = (myCommand*)b;

	wchar_t copy[2];
	copy[0] = ptrParser->input.strContent[ptrParser->currentIndex];
	copy[1] = L'\0';
	writeString(&ptrCmd->name, copy);
	++ptrParser->currentIndex;

	return true;

}

/**
 **
 **   add option
 **/
bool funAddOption(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myCommand* ptrCmd = (myCommand*)b;

	wchar_t copy[2];
	copy[0] = ptrParser->input.strContent[ptrParser->currentIndex];
	copy[1] = L'\0';
	writeString(&ptrCmd->option, copy);
	++ptrParser->currentIndex;

	return true;
}

/**
 **
 **   init parameter
 **/
bool funInitParameter(myPtrGirlParser a, void* b) {

	myCommand* ptrCmd = (myCommand*)b;

	ptrCmd->currentParameter = 0;

	return true;
}


/**
 **
 **   add parameter
 **/
bool funAddParameter(myPtrGirlParser a, void* b) {

	myGirlParser* ptrParser = (myGirlParser*)a;
	myCommand* ptrCmd = (myCommand*)b;

	++ptrCmd->currentParameter;
	if (ptrCmd->currentParameter == ptrCmd->parameters.used) {

		/** fin de l'analyse **/
		if (ptrParser->currentIndex + 1 == ptrParser->input.used)
			ptrParser->currentState = 2;
		else
		{
			wprintf(L"funAddParameter error : number of parameters too long");
			exit(EXIT_FAILURE);
		}

	}
	else {

		/** caractère , **/
		if (!ptrParser->input.strContent[ptrParser->currentIndex] == L',')
		{
			wprintf(L"funAddParameter error : number of parameters too short");
			exit(EXIT_FAILURE);
		}
	}

	return true;
}

/**
 **
 **   add first keyword
 **/
void addKeywordName(myGirlParser* p, myString keyword, int c, int *max, int* next) {

	if (!searchKeyword(p, c, next)) {

		++(*max);
		addKeyword(p, setIntList(1, c), 1, setStringList(1, keyword.strContent), 1, *max);
		/** register any word **/
		addAction(p, setIntList(1, *max), 1, setStringList(1, L"funAddOption"), setActionList(1, funAddOption), 1);
		*next = *max;
		/** space at any case draws next step **/
		addLookahead(p, setIntList(1, *max), 1, setCharList(2, L' ', L'\t'), 2, (*max) + 1);
		++(*max);
	}

}


/**
**
**   add first keyword (without option)
**/
void addKeywordName2(myGirlParser* p, myString keyword, int c, int *max, int* next) {

	if (!searchKeyword(p, c, next)) {

		addKeyword(p, setIntList(1, c), 1, setStringList(1, keyword.strContent), 1, 2);
	}

}


bool funCreateSubParser(myPtrGirlParser a, void* b);
/**
 **
 **   add second keyword
 **/
void addKeywordOption(myGirlParser* p, myString keyword, int c, int *max, int* next) {

	if (!searchKeyword(p, c, next)) {

		++(*max);
		addKeyword(p, setIntList(1, c), 1, setStringList(1, keyword.strContent), 1, *max);
		/** register any word **/
		addAction(p, setIntList(1, *max), 1, setStringList(3, L"funInitParameter", L"funCreateSubParser", L"funAddParameter"), setActionList(3, funInitParameter, funCreateSubParser, funAddParameter), 3);
	}

}


/**
 **
 **  create sub Parser
 **/
bool funCreateSubParser(myPtrGirlParser a, void* b) {

	myGirlParser* currentParser = (myGirlParser*)a;
	myCommand* currentCommand = (myCommand*)b;

	int current, next, maxCurrent = 2;
	wchar_t* ws = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	myString s = createString(0);
	writeString(&s, ws);

	myGirlParser g = createGirlParser(1, setIntList(1, 2), 1, s);
	myGirlParser* ptrParser = &g;

	myCommand* p = (myCommand*)(model.currentSession->specifics.element);

	for (int indexCommand = 0; indexCommand < model.currentSession->specifics.used; ++indexCommand) {


		myCommand* ptrCmd = &p[indexCommand];

		/** draws a sequence example for this command **/
		/** if sequence has not been registered into parser, add it now **/
		ptrParser->currentIndex = 0;
		clearString(&ptrParser->input);
		writeString(&ptrParser->input, ptrCmd->name.strContent);
		writeString(&ptrParser->input, L" ");
		writeString(&ptrParser->input, ptrCmd->option.strContent);
		writeString(&ptrParser->input, L" ");

		wprintf(ptrParser->input.strContent);

		myCommand* pr = (myCommand*)ptrCmd->parameters.element;
		for (int indexParam = 0; indexParam < ptrCmd->parameters.used; ++indexParam) {

			if (indexParam > 0)
				writeString(&ptrParser->input, L",");
			writeString(&ptrParser->input, pr[indexParam].name.strContent);

		}

		current = 1;
		if (ptrCmd->option.used > 0) {
			addKeywordName(ptrParser, ptrCmd->name, current, &maxCurrent, &next);
			addKeywordOption(ptrParser, ptrCmd->option, next, &maxCurrent, &next);
		}
		else {
			addKeywordName2(ptrParser, ptrCmd->name, current, &maxCurrent, &next);
		}

	}

	dumpGirlParser(ptrParser);

	myCommand result = createCommand();
	myString source = createString(0);
	writeString(&source, currentParser->input.strContent + currentParser->currentIndex);
	if (process(&g, &source, &result)) {

		wchar_t s[256];
		swprintf(s, 255, L"%ls %ls \n", result.name.strContent, result.option.strContent);
		wprintf(s);
		writeString(&((myCommand*)currentCommand->parameters.element)[currentCommand->currentParameter].value, s);
		return true;

	}

	return false;
}


bool createParser(myString input, myCommand* result) {

	wchar_t* ws = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	myString s = createString(0);
	writeString(&s, ws);

	int current = 1, next = 0, maxCurrent = 2;
	myGirlParser g = createGirlParser(1, setIntList(1, 2), 1, s);
	myGirlParser* ptrParser = &g;

	myCommand* p = (myCommand*)(builtInCommands.element);

	for (int indexCommand = 0; indexCommand < builtInCommands.used; ++indexCommand) {

		myCommand* ptrCmd = &p[indexCommand];

		/** draws a sequence example for this command **/
		/** if sequence has not been registered into parser, add it now **/
		ptrParser->currentIndex = 0;
		clearString(&ptrParser->input);
		writeString(&ptrParser->input, ptrCmd->name.strContent);
		writeString(&ptrParser->input, L" ");
		writeString(&ptrParser->input, ptrCmd->option.strContent);
		writeString(&ptrParser->input, L" ");

		wprintf(ptrParser->input.strContent);

		myCommand* pr = (myCommand*)ptrCmd->parameters.element;
		for (int indexParam = 0; indexParam < ptrCmd->parameters.used; ++indexParam) {

			if (indexParam > 0)
				writeString(&ptrParser->input, L",");
			writeString(&ptrParser->input, pr[indexParam].name.strContent);

		}

		current = 1;
		current = 1;
		if (ptrCmd->option.used > 0) {
			addKeywordName(ptrParser, ptrCmd->name, current, &maxCurrent, &next);
			addKeywordOption(ptrParser, ptrCmd->option, next, &maxCurrent, &next);
		}
		else {
			addKeywordName2(ptrParser, ptrCmd->name, current, &maxCurrent, &next);
		}



	}


	dumpGirlParser(ptrParser);

	if (process(&g, &input, result)) {

		wprintf(L"%ls %ls \n", result->name.strContent, result->option.strContent);
		return true;

	}

	return false;

}