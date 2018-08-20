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
#include "girlParser.h"
#include "csv-reader.h"

/**
 **   Crée une liste limitée
 **   capacity : capacité maximum
 **/
myCSV createCSV(unsigned int capacity) {
    
    
    myCSV m;
    m.attributes = (myList*)malloc(sizeof(myList) * (capacity + 1));
    if (m.attributes != NULL) {
        
        m.capacity = capacity;
        m.used = 0;
        memset(m.attributes, 0, sizeof(myList));
        return m;
        
    } else {
        
        perror("Erreur dans createCSV : ");
        exit(EXIT_FAILURE);
    }
    
}


/**
 **   Libère la mémoire
 **   myCSV : données
 **/
void freeCSV(myCSV* csv) {
    
    myList* current = csv->attributes;
    
    int index;
    for(index = 0; index < csv->used; ++index, ++current) {
        
        freeList(current);
        
    }
    
    free(csv->attributes);
    csv->capacity = 0;
    csv->used = 0;

}

/**
 **  Read an attribute
 **/
void readAttribute(FILE* csvFile, myString output) {
    
    
}

/**
 **  Function for parse
 **/
bool CsvReader(myString* input, void* a, void* b) {
    
    myGirlParser* g = (myGirlParser*)a;
    myCSV* csv = (myCSV*)b;
    
    return false;
}


/**
 **  Load a CSV file
 **/
void csvLoader(char* fileName) {
    
    int e[3] = {1,2,3};
    myGirlParser g = createGirlParser(1, e, 3);
    myCSV m = createCSV(MINSIZE);
    readFromFile(fileName, CsvReader, &g, &m);
    
}

