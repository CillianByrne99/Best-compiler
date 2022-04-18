#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
 
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

// adds a node to the hash table
void insert(char *name, int len, int type, int lineno){
    unsigned int hashval = hash(name);
    nodeList *l = hash_table[hashval];
    while ((l != NULL) && (strcmp(name,l->st_name) != 0)) l = l->next;
    if (l == NULL){
        l = (nodeList*) malloc(sizeof(nodeList));
        strncpy(l->st_name, name, len);  
        l->st_type = type;
        l->scope = cur_scope;
        l->lines = (listOfRefs*) malloc(sizeof(listOfRefs));
        l->lines->lineno = lineno;
        l->lines->next = NULL;
        l->next = hash_table[hashval];
        hash_table[hashval] = l; 
        printf("Testing your input!\n"); 
    }
    else{
        l->scope = cur_scope;
        listOfRefs *t = l->lines;
        while (t->next != NULL) t = t->next;
        t->next = (listOfRefs*) malloc(sizeof(listOfRefs));
        t->next->lineno = lineno;
        t->next->next = NULL;
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
 

