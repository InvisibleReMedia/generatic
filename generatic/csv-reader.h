//
//  csv-reader.h
//  generatic
//
//  Created by Olivier on 18/08/2018.
//  Copyright © 2018 Olivier. All rights reserved.
//

#ifndef csv_reader_h
#define csv_reader_h

typedef struct {
    
    myList* lines;
    unsigned int used;
    unsigned int capacity;
    myList newLine;
    myList columns;
    myString currentAttribut;
    unsigned int index;
    
} myCSV;

extern myCSV createCSV(unsigned int);
extern void freeCSV(myCSV*);
extern void csvLoader(char *);


#endif /* csv_reader_h */
