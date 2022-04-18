#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ToY.h"
 
/* current scope */
int cur_scope = 0;
 
void table(){
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
        printf("Testing your %s input %d!\n", name, lineno); // error checking
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
        printf("Testing %s your input %d!\n", name, lineno);
    }
}

