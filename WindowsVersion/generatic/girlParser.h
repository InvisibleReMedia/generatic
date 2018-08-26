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


/**
 **  A context swap
 **
 **/
typedef struct {

	int* ints;
	unsigned int capacity;
	unsigned int used;
} myContext;

/**
 **   A rule
 **/
typedef struct {

	myString name;				/** rule name **/
	int* states;				/** states **/
	unsigned int countState;	/** count of states **/

} myRule;

/**
 **   A rule list
 **/
typedef struct {

	myRule*			list;		/** rules **/
	unsigned int	used;		/** active rules **/
	unsigned int	capacity;	/** container size **/

} myRuleList;

/**
 **  Lookahead
 **/
typedef struct {
    
    int* state_for;             /** list of state for */
    unsigned int countState;    /** count of state for */
    wchar_t* if_c;              /** change state if these chars **/
    unsigned int countChars;    /** count of char **/
    int state_next;             /** go to this state **/

} myLookahead;

/**
 **  Lookahead list
 **/
typedef struct {
    
    myLookahead* list;
    unsigned int used;
    unsigned int capacity;
    
} myLookaheadList;

typedef struct {
    
    int* state_for;             /** list of state for */
    unsigned int countState;    /** count of state for */
    myString* if_s;             /** change state if these string **/
    unsigned int countStrings;  /** count of string **/
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
    
    int*			states_at;              /** at these states **/
	myString*		functionNames;			/** function names **/
    unsigned int	countState;				/** count state **/
    action*			functions;				/** call these fuctions **/
    unsigned int	countFunctions;			/** count functions **/
    
} myAction;

typedef struct {
    
    myAction* actions;          /** action list **/
    unsigned int used;
    unsigned int capacity;
    
} myActionList;

typedef struct {
    
    int*            states_at;              /** at these states **/
    myString*       functionNames;          /** function names **/
    unsigned int    countState;             /** count state **/
    interpret*      functionals;            /** call these fuctions **/
    unsigned int    countFunctions;         /** count functions **/

} myFunctional;

typedef struct {
    
    myFunctional*   funs;          /** functional functions **/
    unsigned int    used;          /** used counter **/
    unsigned int    capacity;      /** allocated size **/
    
} myFunctionalList;

typedef struct {
    
    myYieldReadPart* reader;            /** file reader **/
    int state_start;                    /** start state **/
    myKeywordList keywords;             /** keyword list **/
    myLookaheadList lookaheads;         /** lookahead list **/
    myAutomaticMoveList autoMoves;      /** auto move list **/
    myActionList works;                 /** action list **/
	myRuleList rules;					/** rules **/
	int* state_end;                     /** states end **/
    unsigned int countState;            /** count states **/

	myRule currentRule;					/** current rule **/
	myKeyword currentKeyword;           /** current keyword **/
	myLookahead currentLook;			/** current lookahead **/
	myAutomaticMove currentMove;		/** current auto move **/
	myAction currentWork;               /** current action **/

    
    bool notAvailable;                  /** when current state at end **/
    int currentState;                   /** current state **/
	myString significantChars;			/** all significant chars (are characters in keyword) **/
	myContext contexts;					/** push or pop context **/
    myFunctionalList functionals;       /** a functional parser **/
    
} myGirlParser;


extern int* setIntList(int, ...);
extern wchar_t* setCharList(int, ...);
extern action* setActionList(int, ...);
extern myString* setStringList(int, ...);
extern myGirlParser createGirlParser(int, int[], unsigned int, myString);
extern bool process(myGirlParser*, myString*, void*);
extern bool yieldprocess(myGirlParser*, void*);
extern void addLookahead(myGirlParser*, int[], unsigned int, wchar_t[], unsigned int, int);
extern void addKeyword(myGirlParser*, int[], unsigned int, myString[], unsigned int, int);
extern void addAutomaticMove(myGirlParser*, int[], unsigned int, int);
extern void addAction(myGirlParser*, int[], unsigned int, myString*, action[], unsigned int);
extern void addRule(myGirlParser*, int[], unsigned int, wchar_t*);

extern myRuleList* writeRule(myRuleList*, myRule*);
extern myRule createRule(int*, unsigned int, wchar_t*);
extern myKeyword createKeyword(int*, unsigned int, myString*, unsigned int, int);
extern void pushContext(myGirlParser*);
extern int popContext(myGirlParser*);

extern bool searchLookahead(myGirlParser*, int, wchar_t, int*);
extern bool searchKeyword(myGirlParser* p, int, int*);
extern bool searchAutomaticMove(myGirlParser*, int, int*);
extern bool searchAction(myGirlParser*, int, myString*, action**, unsigned int*);
extern bool searchRule(myGirlParser*, int, myString*, action**, unsigned int*);
extern void freeGirlParser(myGirlParser*);
extern void freeLookahead(myLookahead*);
extern void freeKeyword(myKeyword*);
extern void freeRule(myRule*);
extern void freeAutomaticMove(myAutomaticMove*);
extern void freeAction(myAction*);
extern void freeLookaheadList(myLookaheadList*);
extern void freeKeywordList(myKeywordList*);
extern void freeAutomaticMoveList(myAutomaticMoveList*);
extern void freeActionList(myActionList*);
extern void dumpGirlParser(myGirlParser*);


#endif /* girlParser_h */
