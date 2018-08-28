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
#include "cmd.h"
#include "parse-cmd.h"
#include <stdarg.h>
#include "PowerShell/fileSystem.h"
#include "exInterpret.h"
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

bool testName(void *a, myExInterpret* l) {
    
    return expression_loop_notin(a, setCharList(3, L' ', L'\t', L'\n'), 3, l);
    
}

bool testParam(void *a, myExInterpret* l) {
    
    return expression_notin(a, setCharList(2, L',', L'\n'), 2, l);
    
}

bool testSpace(void *a, myExInterpret* l) {
    
    return expression_loop_in(a, setCharList(3, L' ', L'\t', L'\n'), 3, l);
    
}

bool testNameAndSpace(void* a, myExInterpret* l) {
    
	return testName(a, l) && activateTrashList(l) && testSpace(a, l);
    
}

bool setParam(void *a, myExInterpret* l) {
    
    myString s = createString(0);
    writeString(&s, L"param");
    bool res = type(a, testParam, s, l);
    freeString(&s);
    return res;

}

bool searchOption(void *a, myExInterpret* l) {
    
    myString s = createString(0);
    writeString(&s, L"option");
    bool res = type(a, testNameAndSpace, s, l);
    freeString(&s);
    return res;
}

bool searchName(bool, void*, myExInterpret*);

bool searchOneParam(void* a, myExInterpret* l) {

	return searchName(false, a, l);

}

bool searchParam(void *a, myExInterpret* l) {

	myString s = createString(0);
	writeString(&s, L"param");
	return type(a, searchOneParam, s, l);
}

bool searchLoopParams(void *a, myExInterpret* l) {

	myString interval = createString(0);
	writeString(&interval, L",");
	myString start = createString(0);
	myString end = createString(0);
	writeString(&end, L"\n");
	bool res = loop(a, interval, testParam, searchParam, start, end, l);
	return res;

}


bool searchName(bool printed, void *a, myExInterpret* l) {
    
    bool res = false;
    bool one = false;
    myCommand lastSelected = createCommand();

	if (l->recorder.used > 0) {

        /** recherche du name dans les commandes **/
        myCommand c = createCommand();
        myCommandList found;
        writeString(&c.name, l->recorder.element[l->recorder.used - 1].value.strContent);

        if (searchCommandName(&c, &found)) {
            
            if (searchOption(a, l)) {
                
                /** recherche de option dans les commandes **/
                writeString(&c.option, l->recorder.element[l->recorder.used - 1].value.strContent);
                myCommandList option;
                if (searchCommandOption(&c, &found, &option)) {
                    
					if (option.used == 1) {

						int startParamIndex = l->recorder.used;
						res = searchLoopParams(a, l);
						int endParamIndex = l->recorder.used;

						myCommand* op = (myCommand*)option.element;
						res = false;
						one = false;
						for (int index = 0; index < option.used; ++index) {

							if (op[index].parameters.used == endParamIndex - startParamIndex) {

								if (!one) {

									one = true;
									lastSelected = op[index];
									for (int countParam = 0; countParam < op[index].parameters.used; ++countParam) {
										writeString(&((myCommand*)lastSelected.parameters.element)[countParam].value, l->recorder.element[startParamIndex + countParam].value.strContent);
									}
									res = true;

								}
								else {

									res = false;

								}

							}
						}


					}
					else {

						if (printed)
							wprintf(L"Je n'ai pas trouvé la commande %ls %ls avec certitude\n", c.name.strContent, c.option.strContent);
						res = false;
					}

                }
				else {

					if (printed)
						wprintf(L"Je n'ai pas trouvé la commande %ls avec l'option %ls\n", c.name.strContent, c.option.strContent);
					res = false;
				}

            }
        }
		else {

			if (printed)
				wprintf(L"Je n'ai pas trouvé la commande %ls\n", c.name.strContent);
			res = false;
		}

    }
    
    return res && one;
}


bool startSearchName(void *a, myExInterpret* l) {

	bool res;
	myString s = createString(0);
	writeString(&s, L"name");
	if (type(a, testNameAndSpace, s, l)) {
		res = searchName(true, a, l);
	}
	else
		res = false;
	freeString(&s);
	return res;
}

bool createParser(myString input, myCommand* result) {

    myString s = createString(0);
    myGirlParser g = createGirlParser(1, setIntList(0), 0, s);
    myYieldReadPart y;
    initStringGirlParser(&g, &y, input);
    createExInterpret(&g, startSearchName);
    freeString(&s);
    return true;
}
