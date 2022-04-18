#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ToY.h"
 
/* current scope */
int cur_scope = 0;
 
void init_hash_table(){
    int i; 
    hash_table = malloc(SIZE * sizeof(nodeList*));
    for(i = 0; i < SIZE; i++) hash_table[i] = NULL;
}
 
unsigned int hash(char *key){
    unsigned int hashval = 0;
    for(;*key!='\0';key++) hashval += *key;
    hashval += key[0] % 11 + (key[0] << 3) - key[0];
    return hashval % SIZE;
}
 
void insert(char *name, int len, int type, int lineno){
    unsigned int hashval = hash(name);
    nodeList *l = hash_table[hashval];
    
    while ((l != NULL) && (strcmp(name,l->st_name) != 0)) l = l->next;
    
    /* variable not yet in table */
    if (l == NULL){
        l = (nodeList*) malloc(sizeof(nodeList));
        strncpy(l->st_name, name, len);  
        /* add to hashtable */
        l->st_type = type;
        l->scope = cur_scope;
        l->lines = (listOfRefs*) malloc(sizeof(listOfRefs));
        l->lines->lineno = lineno;
        l->lines->next = NULL;
        l->next = hash_table[hashval];
        hash_table[hashval] = l; 
        printf("Inserted %s for the first time with linenumber %d!\n", name, lineno); // error checking
    }
    /* found in table, so just add line number */
    else{
        l->scope = cur_scope;
        listOfRefs *t = l->lines;
        while (t->next != NULL) t = t->next;
        /* add linenumber to reference list */
        t->next = (listOfRefs*) malloc(sizeof(listOfRefs));
        t->next->lineno = lineno;
        t->next->next = NULL;
        printf("Found %s again at line %d!\n", name, lineno);
    }
}
 
nodeList *lookup(char *name){ /* return symbol if found or NULL if not found */
    unsigned int hashval = hash(name);
    nodeList *l = hash_table[hashval];
    while ((l != NULL) && (strcmp(name,l->st_name) != 0)) l = l->next;
    return l; // NULL is not found
}
 
nodeList *lookup_scope(char *name, int scope){ /* return symbol if found or NULL if not found */
    unsigned int hashval = hash(name);
    nodeList *l = hash_table[hashval];
    while ((l != NULL) && (strcmp(name,l->st_name) != 0) && (scope != l->scope)) l = l->next;
    return l; // NULL is not found
}
 
void hide_scope(){ /* hide the current scope */
    if(cur_scope > 0) cur_scope--;
}
 
void incr_scope(){ /* go to next scope */
    cur_scope++;
}
 
/* print to stdout by default */ 
void ToY_dump(FILE * of){  
  int i;
  fprintf(of,"------------ ------ ------------\n");
  fprintf(of,"Name         Type   Line Numbers\n");
  fprintf(of,"------------ ------ -------------\n");
  for (i=0; i < SIZE; ++i){ 
    if (hash_table[i] != NULL){ 
        nodeList *l = hash_table[i];
        while (l != NULL){ 
            listOfRefs *t = l->lines;
            fprintf(of,"%-12s ",l->st_name);
            if (l->st_type == INT_TYPE) fprintf(of,"%-7s","int");
            else if (l->st_type == REAL_TYPE) fprintf(of,"%-7s","real");
            else if (l->st_type == STR_TYPE) fprintf(of,"%-7s","string");
            else if (l->st_type == ARRAY_TYPE){
                fprintf(of,"array of ");
                if (l->inf_type == INT_TYPE)           fprintf(of,"%-7s","int");
                else if (l->inf_type  == REAL_TYPE)    fprintf(of,"%-7s","real");
                else if (l->inf_type  == STR_TYPE)     fprintf(of,"%-7s","string");
                else fprintf(of,"%-7s","undef");
            }
            else if (l->st_type == FUNCTION_TYPE){
                fprintf(of,"%-7s %s","function returns ");
                if (l->inf_type == INT_TYPE)           fprintf(of,"%-7s","int");
                else if (l->inf_type  == REAL_TYPE)    fprintf(of,"%-7s","real");
                else if (l->inf_type  == STR_TYPE)     fprintf(of,"%-7s","string");
                else fprintf(of,"%-7s","undef");
            }
            else fprintf(of,"%-7s","undef"); // if UNDEF or 0
            while (t != NULL){
                fprintf(of,"%4d ",t->lineno);
            t = t->next;
            }
            fprintf(of,"\n");
            l = l->next;
        }
    }
  }
}