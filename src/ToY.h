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

void table();
unsigned int hash(char *key); 
void insert(char *name, int len, int type, int lineno); 


typedef struct parameterStruct{
    int type;
    char name[LENGTH];
    int x; double y; char *st_sval;
    int passing;
}parameterStruct;
 
typedef struct listOfRefs{ 
    int lineno;
    struct listOfRefs *next;
    int type;
}listOfRefs;

typedef struct nodeList{
    char st_name[LENGTH];
    int st_size;
    int scope;
    listOfRefs *lines;
    int store_x; double store_y; char *store_sval;
    int st_type;
    int inf_type;
    int *x_vals; double *y_vals; char **store_vals;
    int array_size;
    parameterStruct *parameterStructeters;
    int num_of_pars;
    struct nodeList *next;
}nodeList;
 
static nodeList **hash_table;

