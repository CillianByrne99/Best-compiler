#define SIZE 211
#define MAXTOKENLEN 40
#define UNDEF 0
#define INT_TYPE 1
#define REAL_TYPE 2
#define STR_TYPE 3
#define LOGIC_TYPE 4
#define ARRAY_TYPE 5
#define FUNCTION_TYPE 6
#define BY_VALUE 1
#define BY_REFER 2

// Function Declarations
// hash table structure
// and functionality for inserting and serching for entries



typedef struct parameterStruct{
    int par_type;
    char parameterStruct_name[MAXTOKENLEN];
    int ival; double fval; char *st_sval;
    int passing; 
}parameterStruct;

 
/* a linked list of references*/

typedef struct listOfRefs{ 
    int lineno;
    struct listOfRefs *next;
    int type;
}listOfRefs;

// This strut referneces a list of nodes
// Stores values and other information
// For arrays it stores info type and for functions in returns type
// it then points to the next object in list
typedef struct nodeList{
    char st_name[MAXTOKENLEN];
    int st_size;
    int scope;
    listOfRefs *lines;
    int st_ival; double st_fval; char *st_sval;
    int st_type;
    int inf_type;
    int *i_vals; double *f_vals; char **s_vals;
    int array_size;
    parameterStruct *parameterStructeters;
    int num_of_pars;
    struct nodeList *next;
}nodeList;
 
static nodeList **hash_table;

void init_hash_table(); 
unsigned int hash(char *key); 
void insert(char *name, int len, int type, int lineno); 
nodeList *lookup(char *name); 
nodeList *lookup_scope(char *name, int scope); 
void hide_scope(); 
void incr_scope(); 