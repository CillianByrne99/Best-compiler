#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ToY.h"
 
int cur_scope = 0;

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
        printf("Testing your input now.....");
    }
    else{
        l->scope = cur_scope;
        listOfRefs *t = l->lines;
        while (t->next != NULL) t = t->next;
        t->next = (listOfRefs*) malloc(sizeof(listOfRefs));
        t->next->lineno = lineno;
        t->next->next = NULL;
        printf("Testing your input now.....");
    }
}
  
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
