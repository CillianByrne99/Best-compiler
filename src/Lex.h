#define SIZE 211
#define LENGTH 40
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

void table();
unsigned int hash(char *key);
void insert(char *name, int len, int type, int lineno);

typedef struct PassedPar{
    int type;
    char name[LENGTH];
    int x; double y; char *st_sval;
    int passing;
}PassedPar;
 
/* a linked list of references*/

typedef struct RefList{ 
    int lineno;
    struct RefList *next;
    int type;
}RefList;
 
// This strut referneces a list of nodes
// Stores values and other information
// For arrays it stores info type and for functions in returns type
// it then points to the next object in list
typedef struct list_t{
    char st_name[LENGTH];
    int st_size;
    RefList *lines;
    int store_x; double store_y; char *store_sval;
    int st_type;
    int inf_type;
    int *x_vals; double *y_vals; char **store_vals;
    int array_size;
    PassedPar *parameters;
    int num_of_pars;
    struct list_t *next;
}list_t;
 
static list_t **hash_table;