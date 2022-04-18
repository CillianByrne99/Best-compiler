/* maximum size of hash table */
#define SIZE 211
 
/* maximum size of tokens-identifiers */
#define MAXTOKENLEN 40
 
/* token types */
#define UNDEF 0
#define INT_TYPE 1
#define REAL_TYPE 2
#define STR_TYPE 3
#define LOGIC_TYPE 4
#define ARRAY_TYPE 5
#define FUNCTION_TYPE 6
 
/* how parameterStructeter is passed */
#define BY_VALUE 1
#define BY_REFER 2
 
/* parameterStructeter struct */
typedef struct parameterStruct{
    int par_type;
    char parameterStruct_name[MAXTOKENLEN];
    // to store value
    int ival; double fval; char *st_sval;
    int passing; // value or reference
}parameterStruct;
 
/* a linked list of references (lineno's) for each variable */
typedef struct listOfRefs{ 
    int lineno;
    struct listOfRefs *next;
    int type;
}listOfRefs;
 
// struct that represents a list node
typedef struct nodeList{
    char st_name[MAXTOKENLEN];
    int st_size;
    int scope;
    listOfRefs *lines;
    // to store value and sometimes more information
    int st_ival; double st_fval; char *st_sval;
    // type
    int st_type;
    int inf_type; // for arrays (info type) and functions (return type)
    // array stuff
    int *i_vals; double *f_vals; char **s_vals;
    int array_size;
    // function parameterStructeters
    parameterStruct *parameterStructeters;
    int num_of_pars;
    // pointer to next item in the list
    struct nodeList *next;
}nodeList;
 
/* the hash table */
static nodeList **hash_table;
 
// Function Declarations
void init_hash_table(); // initialize hash table
unsigned int hash(char *key); // hash function 
void insert(char *name, int len, int type, int lineno); // insert entry
nodeList *lookup(char *name); // search for entry
nodeList *lookup_scope(char *name, int scope); // search for entry in scope
void hide_scope(); // hide the current scope
void incr_scope(); // go to next scope
void ToY_dump(FILE *of); // dump file