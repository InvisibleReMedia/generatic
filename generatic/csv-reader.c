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
#include "fileSystem.h"
#include <stdarg.h>
#include "girlParser.h"
#include "csv-reader.h"

/**
 **   Crée une liste limitée
 **   capacity : capacité maximum
 **/
myCSV createCSV(unsigned int capacity) {
    
    
    myCSV m;
    m.lines = (myList*)malloc(sizeof(myList) * (capacity + 1));
    if (m.lines != NULL) {
        
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
 **   Les données dans la liste ne doivent pas être détruites
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
    
    writeCSVLine(m, &m->newLine);
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
    csv->capacity = 0;
    csv->used = 0;

}


/**
 **  Function for parse
 **/
bool CsvReader(myString* input, void* a, void* b) {
    
    
    return process(a, input, b);
    
}

bool funAddChar(myPtrGirlParser a, void* b) {
    
    myGirlParser* p = (myGirlParser*)a;
    myCSV* csv = (myCSV*)b;
    wchar_t input[2];
    input[1] = L'\0';
    input[0] = p->input.strContent[p->currentIndex];
    writeString(&csv->currentAttribut, input);
    ++p->currentIndex;
    return true;
}

bool funAddColumn(myPtrGirlParser a, void* b) {
    
    myGirlParser* p = (myGirlParser*)a;
    ++p->currentIndex;
    addColumn(b);
    return true;
}

bool funAddValue(myPtrGirlParser a, void* b) {
    
    myGirlParser* p = (myGirlParser*)a;
    ++p->currentIndex;
    addAttribute(b);
    return true;
    
}


bool funNewLine(myPtrGirlParser a, void* b) {
    
    myGirlParser* p = (myGirlParser*)a;
    ++p->currentIndex;
    addLine(b);
    return true;
}

bool funEndColumn(myPtrGirlParser a, void* b) {
    
    myGirlParser* p = (myGirlParser*)a;
    ++p->currentIndex;
    endColumn(b);
    return true;
}


/**
 **  Load a CSV file
 **/
void csvLoader(char* fileName) {
    
    myGirlParser g = createGirlParser(1, setIntList(1, 9), 1);

    /** fin de fichier **/
    addLookahead(&g, setIntList(4, 1, 4, 6, 7), 4, setCharList(1, L'\xFE'), 1, 9);
    /** etat 1 : first line **/
    /** mange les espaces */
    addLookahead(&g, setIntList(1, 1), 1, setCharList(2, L' ', L'\t'), 2, 1);
    /** etat 1 : accepte , ou \n **/
    addLookahead(&g, setIntList(1, 1), 1, setCharList(1, L','), 1, 2);
    addLookahead(&g, setIntList(1, 1), 1, setCharList(1, L'\n'), 1, 3);
    addAction(&g, setIntList(1, 1), 1, setActionList(1, funAddChar), 1);
    
    /** etat 2 et 3 : automatic redirection **/
    addAutomaticMove(&g, setIntList(1, 2), 1, 1);
    addAutomaticMove(&g, setIntList(1, 3), 1, 4);
    /** etat 2 : add column **/
    addAction(&g, setIntList(1, 2), 1, setActionList(1, funAddColumn), 1);
    /** etat 3 : add line **/
    addAction(&g, setIntList(1, 3), 1, setActionList(2, funAddColumn, funEndColumn), 2);
    
    /** etat 4 : next line **/
    /** mange les espaces */
    addLookahead(&g, setIntList(1, 4), 1, setCharList(2, L' ', L'\t'), 2, 4);
    /** automatic move **/
    addAutomaticMove(&g, setIntList(1, 4), 1, 7);
    /** etat 4 : accepte , \n et " **/
    addLookahead(&g, setIntList(1, 4), 1, setCharList(1, L','), 1, 5);
    addLookahead(&g, setIntList(1, 4), 1, setCharList(1, L'\n'), 1, 10);
    addLookahead(&g, setIntList(1, 4), 1, setCharList(1, L'"'), 1, 6);
    
    /** etat 5 : next column **/
    addAction(&g, setIntList(1, 5), 1, setActionList(1, funAddValue), 1);
    addAutomaticMove(&g, setIntList(1, 5), 1, 4);
    
    /** etat 6 : start quoted column **/
    addAction(&g, setIntList(1, 6), 1, setActionList(1, funAddChar), 1);
    addLookahead(&g, setIntList(1, 6), 1, setCharList(1, L'\\'), 1, 7);
    addLookahead(&g, setIntList(1, 6), 1, setCharList(1, L'"'), 1, 4);

    /** etat 7 : escaped chars **/
    addAutomaticMove(&g, setIntList(1, 7), 1, 4);
    addAction(&g, setIntList(1, 7), 1, setActionList(1, funAddChar), 1);
    
    /** etat 10 : new line **/
    addAction(&g, setIntList(1, 10), 1, setActionList(2, funAddValue, funNewLine), 2);
    addAutomaticMove(&g, setIntList(1, 10), 1, 4);

    
    myCSV m = createCSV(MINSIZE);
    readFromFile(fileName, CsvReader, &g, &m);
    
    for(int indexColumn = 0; indexColumn < m.columns.used; ++indexColumn) {
        
        if (indexColumn > 0)
            wprintf(L" ");
        wprintf(L"%ls", m.columns.list[indexColumn].name.strContent);
        
    }
    wprintf(L"\n");
    for(int indexLine = 0; indexLine < m.used; ++indexLine) {

        for(int indexColumn = 0; indexColumn < m.lines[indexLine].used; ++indexColumn) {
            
            if (indexColumn > 0)
                wprintf(L" ");
            wprintf(L"%ls", m.lines[indexLine].list[indexColumn].value.strContent);
            
        }
        wprintf(L"\n");

    }
    
}

