/*
*
*/

#define NUM_AREA_CODES 430

#define CITY_MAX_NAME 30

/*
* Struct for an area code
*/
typedef struct area_code {
    int code;
    char city[CITY_MAX_NAME];
} AREA_CODE;

/*
* Struct for an entry in the address translator
*/
typedef struct TransEntry {
	bool dest;    //contains DEST
	bool brte;    //contains BRTE
	bool ambnpa;  //contains "AMB NPA"
	bool ambco;   //contains "AMB CO"
	int iscode;   //in state code (3 digits)
	int oscode;   //out of state code (4 digits)
} TRANS_ENTRY;	

/** Node for linked list of TransEntries. */
struct TransEntryStruct {

  /** Cookie pointer */
  TRANS_ENTRY *tentry;

  /** Pointer to the next node. */
  struct TransEntryStruct *next;
};

// A short type name to use for a node.
typedef struct TransEntryStruct TNODE;

/* Array of Area Codes */
AREA_CODE area_code[NUM_AREA_CODES];

/* Output File */
FILE *output;