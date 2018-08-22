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
    
	myString fileName;				/** nom du fichier **/
	myList* lines;					/** lignes **/
	unsigned int used;				/** quantité de lignes **/
	unsigned int capacity;			/** allocation totale des lignes **/
	myList newLine;					/** nouvelle ligne en cours de traitement **/
	myList columns;					/** list des colonnes **/
	myString currentAttribut;		/** attribut courant **/
	unsigned int index;				/** numéro de colonne en cours **/
    
} myCSV;

extern myCSV createCSV(unsigned int, wchar_t*);
extern void freeCSV(myCSV*);
extern myCSV csvLoader(char *);
extern void dumpCSV(myCSV*);
extern bool getLineFromColumnName(myCSV*, wchar_t*, wchar_t*, myList**);
extern bool ImportCommands(myCSV*, myCommandList*);

#endif /* csv_reader_h */
