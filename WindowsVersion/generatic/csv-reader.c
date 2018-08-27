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
#include "csv-reader.h"

/**
 **   Crée une liste limitée
 **   capacity : capacité maximum
 **   name : nom du fichier
 **/
myCSV createCSV(unsigned int capacity, wchar_t* name) {
    
    
    myCSV m;
    m.lines = (myList*)malloc(sizeof(myList) * (capacity + 1));
    if (m.lines != NULL) {
        
		m.fileName = createString((unsigned int)wcslen(name));
		writeString(&m.fileName, name);
        m.capacity = capacity;
        m.used = 0;
        memset(m.lines, 0, sizeof(myList));
        m.newLine = createList(0);
        m.columns = createList(0);
        m.currentAttribut = createString(MINSIZE);
        m.index = 0;
        return m;
        
    } else {
        
        perror("Erreur dans createCSV : ");
        exit(EXIT_FAILURE);
    }
    
}

/**
 **  Realloc line
 **
 **/
myCSV* reallocLine(myCSV* la, unsigned int newCapacity) {
    
    myList* newAlloc = (myList*)realloc(la->lines, sizeof(myList) * (newCapacity + 1));
    if (newAlloc != NULL) {
        
        la->lines = newAlloc;
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
 **   Les données dans la liste fournie en paramètre ne doivent pas être détruites
 **   myCSV : list
 **   myList : object
 **/
myCSV* writeCSVLine(myCSV* m, myList* la) {
    
    if (m->used == 0) {
        
        if (m->capacity < 2) {
            reallocLine(m, 2);
        }
        memcpy(&m->lines[m->used], la, sizeof(myList));
        m->used = 1;
        
    } else if (m->used + 1 < m->capacity) {
        
        memcpy(&m->lines[m->used], la, sizeof(myList));
        m->used += 1;
        
    } else {
        
        reallocLine(m, m->capacity + MINSIZE);
        memcpy(&m->lines[m->used], la, sizeof(myList));
        m->used += 1;
        
    }
    
    return m;
    
}

/**
 **   Add attribute
 **
 **/
void addAttribute(myCSV* m) {
    
    writeList(&m->newLine, m->columns.list[m->index].question.strContent, m->columns.list[m->index].name.strContent, m->currentAttribut.strContent);
    clearString(&m->currentAttribut);
    ++m->index;
    
}

/**
 **   Add column
 **
 **/
void addColumn(myCSV* m) {
    
    writeList(&m->columns, L"", m->currentAttribut.strContent, L"");
    clearString(&m->currentAttribut);
    ++m->index;
    
}

/**
 **   Add line
 **/
void addLine(myCSV* m) {
    
	if (m->index == 3) {
		writeCSVLine(m, &m->newLine);
	}
	m->newLine = createList(0);
	clearString(&m->currentAttribut);
	m->index = 0;
}

/**
 **   At end of column
 **/
void endColumn(myCSV* m) {
    
    clearString(&m->currentAttribut);
    m->index = 0;
    
}


/**
 **   Libère la mémoire
 **   myCSV : données
 **/
void freeCSV(myCSV* csv) {
    
    myList* current = csv->lines;
    
    int index;
    for(index = 0; index < csv->used; ++index, ++current) {
        
        freeList(current);
        
    }
    
    free(csv->lines);
    freeList(&csv->newLine);
    freeList(&csv->columns);
    freeString(&csv->currentAttribut);

	memset(csv, 0, sizeof(myCSV));

}


/**
 **   Find a line from a column name and value
 **/
bool getLineFromColumnName(myCSV* src, wchar_t* columnName, wchar_t* value, myList** pItem) {

	bool found = false;
	for (int indexLine = 0; indexLine < src->used && !found; ++indexLine) {

		for (int indexColumn = 0; indexColumn < src->columns.used && !found; ++indexColumn) {

			if (wcscmp(src->columns.list[indexColumn].name.strContent, columnName) == 0 && wcscmp(src->lines[indexLine].list[indexColumn].value.strContent, value) == 0) {

				*pItem = &src->lines[indexLine];
				found = true;

			}

		}

	}

	return found;
}

/**
 **   Imports commands from csv
 **   Verify that csv has Command,Option,Text(?) as columns
 **/
bool ImportCommands(myCSV* src, myCommandList* dest) {

	wchar_t bypass; /** bypass character **/
	if (src->columns.used == 3) {

		myString header = createString(20);
		writeString(&header, L"Command");
		if (compareString(src->columns.list[0].name, header) == 0) {

			clearString(&header);
			writeString(&header, L"Option");
			if (compareString(src->columns.list[1].name, header) == 0) {

				bypass = src->columns.list[2].name.strContent[5];

				for (int indexLine = 0; indexLine < src->used; ++indexLine) {

					myCommand c = createCommand();
					c.byPass = bypass;
					writeString(&c.name, src->lines[indexLine].list[0].value.strContent);
					writeString(&c.option, src->lines[indexLine].list[1].value.strContent);
					// parameters
					// execCommand (common function)
				}
			}
		}

	}

	return true;
}


/**
 **  Function for parse
 **/
bool CsvReader(myYieldReadPart* p, void* a, void* b) {
    
    myGirlParser* ptrParser = (myGirlParser*)a;
    ptrParser->reader = p;
    return yieldprocess(ptrParser, b);
    
}

bool funAddChar(myPtrGirlParser a, void* b) {
    
    myGirlParser* p = (myGirlParser*)a;
    myCSV* csv = (myCSV*)b;
    wchar_t input[2];
    input[1] = L'\0';
    if (!yieldnReadOut(p->reader, 1)) return false;
    input[0] = p->reader->line.strContent[p->reader->pos];
    writeString(&csv->currentAttribut, input);
    ++p->reader->pos;
    return true;
}

bool funAddEscapeChar(myPtrGirlParser a, void* b) {

	myGirlParser* p = (myGirlParser*)a;
	myCSV* csv = (myCSV*)b;
	wchar_t input[3];
    if (!yieldnReadOut(p->reader, 1)) return false;
	if (p->reader->line.strContent[p->reader->pos] == L'\\' || p->reader->line.strContent[p->reader->pos] == L'"') {
		input[0] = p->reader->line.strContent[p->reader->pos];
		input[1] = L'\0';
		input[2] = L'\0';
	}
	else {
		input[0] = L'\\';
		input[1] = p->reader->line.strContent[p->reader->pos];
		input[2] = L'\0';
	}
	writeString(&csv->currentAttribut, input);
    ++p->reader->pos;
	return true;
}

bool funAddColumn(myPtrGirlParser a, void* b) {
    
    addColumn(b);
    return true;
}

bool funAddValue(myPtrGirlParser a, void* b) {
    
    addAttribute(b);
    return true;
    
}


bool funNewLine(myPtrGirlParser a, void* b) {
    
    addLine(b);
    return true;
}

bool funEndColumn(myPtrGirlParser a, void* b) {
    
    endColumn(b);
    return true;
}

/**
 **   Print CSV
 **/
void dumpCSV(myCSV* m) {

	for (int indexColumn = 0; indexColumn < m->columns.used; ++indexColumn) {

		if (indexColumn > 0)
			wprintf(L" ");
		wprintf(L"%ls", m->columns.list[indexColumn].name.strContent);

	}
	wprintf(L"\n");
	for (int indexLine = 0; indexLine < m->used; ++indexLine) {

		for (int indexColumn = 0; indexColumn < m->lines[indexLine].used; ++indexColumn) {

			if (indexColumn > 0)
				wprintf(L" ");
			wprintf(L"%ls", m->lines[indexLine].list[indexColumn].value.strContent);

		}
		wprintf(L"\n");

	}

}

/**
 **  Load a CSV file
 **/
myCSV csvLoader(char* fileName) {
    
	/** transforms a char into wchar_t **/
	wchar_t f[256];
	int len = (unsigned int)strlen(fileName);
	assert(len < 254);
	for (int index = 0; index < len; ++index) {
		f[index] = (wchar_t)fileName[index];
	}

	myString s = createString(0);
	writeString(&s, L"abcdefghijklmnopqurstuvwxyzABCDEFGHIJKLMNOPQURSTUVWXYS_");
    myGirlParser g = createGirlParser(1, setIntList(1, 9), 1, s);

    /** fin de fichier **/
    addLookahead(&g, setIntList(4, 1, 4, 6, 7), 4, setCharList(1, L'\xFE'), 1, 9);
    /** etat 1 : first line **/
    /** mange les espaces */
    addLookahead(&g, setIntList(1, 1), 1, setCharList(2, L' ', L'\t'), 2, 1);
    /** etat 1 : accepte , ou \n **/
    addLookahead(&g, setIntList(1, 1), 1, setCharList(1, L','), 1, 2);
    addLookahead(&g, setIntList(1, 1), 1, setCharList(1, L'\n'), 1, 3);
	addAction(&g, setIntList(1, 1), 1, setStringList(1, L"funAddChar"), setActionList(1, funAddChar), 1);
    
    /** etat 2 et 3 : automatic redirection **/
    addAutomaticMove(&g, setIntList(1, 2), 1, 1);
    addAutomaticMove(&g, setIntList(1, 3), 1, 4);
    /** etat 2 : add column **/
	addAction(&g, setIntList(1, 2), 1, setStringList(1, L"funAddColumn"), setActionList(1, funAddColumn), 1);
    /** etat 3 : add line **/
	addAction(&g, setIntList(1, 3), 1, setStringList(2, L"funAddColumn", L"funEndColumn"), setActionList(2, funAddColumn, funEndColumn), 2);
    
    /** etat 4 : next line **/
    /** mange les espaces */
    addLookahead(&g, setIntList(1, 4), 1, setCharList(2, L' ', L'\t'), 2, 4);
    /** automatic move **/
    addAutomaticMove(&g, setIntList(1, 4), 1, 11);
    /** etat 4 : accepte , \n et " **/
	addLookahead(&g, setIntList(1, 4), 1, setCharList(1, L','), 1, 5);
    addLookahead(&g, setIntList(1, 4), 1, setCharList(1, L'\n'), 1, 10);
    addLookahead(&g, setIntList(1, 4), 1, setCharList(1, L'"'), 1, 6);
    
    /** etat 5 : next column **/
	addAction(&g, setIntList(1, 5), 1, setStringList(1, L"funAddValue"), setActionList(1, funAddValue), 1);
    addAutomaticMove(&g, setIntList(1, 5), 1, 4);
    
    /** etat 6 : start quoted column **/
	addAction(&g, setIntList(1, 6), 1, setStringList(1, L"funAddChar"), setActionList(1, funAddChar), 1);
    addLookahead(&g, setIntList(1, 6), 1, setCharList(1, L'\\'), 1, 7);
    addLookahead(&g, setIntList(1, 6), 1, setCharList(1, L'"'), 1, 4);

    /** etat 7 : escaped chars **/
    addAutomaticMove(&g, setIntList(1, 7), 1, 6);
	addAction(&g, setIntList(1, 7), 1, setStringList(1, L"funAddEscapeChar"), setActionList(1, funAddEscapeChar), 1);
    
    /** etat 10 : new line **/
	addAction(&g, setIntList(1, 10), 1, setStringList(2, L"funAddValue", "funNewLine"), setActionList(2, funAddValue, funNewLine), 2);
    addAutomaticMove(&g, setIntList(1, 10), 1, 4);

	/** etat 11 : accepte , \n **/
	addAction(&g, setIntList(1, 11), 1, setStringList(1, L"funAddChar"), setActionList(1, funAddChar), 1);
	addLookahead(&g, setIntList(1, 11), 1, setCharList(1, L','), 1, 5);
	addLookahead(&g, setIntList(1, 11), 1, setCharList(1, L'\n'), 1, 10);

    myCSV m = createCSV(MINSIZE, f);
	yieldReadFromFile(fileName, CsvReader, &g, &m);
    
	freeGirlParser(&g);

	return m;
}

