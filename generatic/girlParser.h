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

#ifndef girlParser_h
#define girlParser_h

typedef struct {
    
    int* state_for;             /** list of state for */
    unsigned int countState;    /** count of state for */
    wchar_t* if_c;              /** change state if these chars **/
    unsigned int countChars;    /** count of char **/
    int state_next;             /** go to this state **/

} myLookahead;

typedef struct {
    
    myLookahead* list;
    unsigned int used;
    unsigned int capacity;
    
} myLookaheadList;

typedef struct {
    
    int* state_for;             /** list of state for */
    unsigned int countState;    /** count of state for */
    myString* if_s;             /** change state if these string **/
    unsigned int countChars;    /** count of string **/
    int state_next;             /** go to this state **/
    
} myKeyword;

typedef struct {
    
    myKeyword* keys;
    unsigned int used;
    unsigned int capacity;
    
} myKeywordList;

typedef struct {
    
    int* state_from;            /** current states from **/
    unsigned int countState;    /** count states */
    int state_to;               /** next state **/
    
} myAutomaticMove;

typedef struct {
    
    myAutomaticMove* moves; /** move list **/
    unsigned int used;
    unsigned int capacity;
    
} myAutomaticMoveList;

typedef void* myPtrGirlParser;
typedef bool (*action)(myPtrGirlParser, void*);

typedef struct {
    
    int*    states_at;              /** at these states **/
    unsigned int countState;        /** count state **/
    action*  functions;             /** call these fuctions **/
    unsigned int countFunctions;    /** count functions **/
    
} myAction;

typedef struct {
    
    myAction* actions;          /** action list **/
    unsigned int used;
    unsigned int capacity;
    
} myActionList;

typedef struct {
    
    int state_start;                    /** start state **/
    myKeywordList keywords;             /** keyword list **/
    myLookaheadList lookaheads;         /** lookahead list **/
    myAutomaticMoveList autoMoves;      /** auto move list **/
    myActionList works;                 /** action list **/
    int* state_end;                     /** states end **/
    unsigned int countState;            /** count states **/
    
    bool notAvalaible;                  /** when current state at end **/
    int currentState;                   /** current state **/
    long currentIndex;                  /** current index of input **/
    myString input;                     /** current input **/
    
} myGirlParser;


extern int* setIntList(int, ...);
extern wchar_t* setCharList(int, ...);
extern action* setActionList(int, ...);
extern myGirlParser createGirlParser(int, int[], unsigned int);
extern bool process(myGirlParser*, myString*, void*);
extern void addLookahead(myGirlParser*, int[], unsigned int, wchar_t[], unsigned int, int);
extern void addKeyword(myGirlParser*, int[], unsigned int, myString[], unsigned int, int);
extern void addAutomaticMove(myGirlParser*, int[], unsigned int, int);
extern void addAction(myGirlParser*, int[], unsigned int, action[], unsigned int);
extern void verifyGirlParser(myGirlParser*);

extern bool searchLookahead(myGirlParser*, int, wchar_t, int*);
extern bool searchAutomaticMove(myGirlParser*, int, int*);
extern bool searchAction(myGirlParser*, int, action**, unsigned int*);


#endif /* girlParser_h */
