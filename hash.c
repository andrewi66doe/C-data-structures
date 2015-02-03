/*
 * =====================================================================================
 *
 *       Filename:  hash.c
 *
 *    Description:  An attempt to implement a hash table in C
 *
 *        Version:  1.0
 *        Created:  02/22/14 11:02:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andrew Walker (), andrewg.walker@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHTABLE_LENGTH 5

struct Node{
    char *string;
    struct Node *next;
};

struct Hashtable{
    struct Node *table;
    int length;
};


struct Node* newNode();
void newHashTable(struct Hashtable *h, int size);
int hash(char *str, int len);
void insert(struct Hashtable *h, char *str);
void insert_ll(struct Node *node, char *str);
void freeHashTable(struct Hashtable *h);
void print_ll(struct Node *node);


int main(int argc, char **argv)
{
    int i;

    struct Hashtable hash_table;
    //Allocate memory for a new hash table
    newHashTable(&hash_table, HASHTABLE_LENGTH);
    printf("New hash table containing no values\n");
    //Print the hash table containing no values
    for(i=0;i<HASHTABLE_LENGTH;i++){
        print_ll(&(hash_table.table[i]));
    }
    putchar('\n');
    //Insert several values into the hash table
    insert(&hash_table, "Hello World");
    insert(&hash_table, "Hello World");
    insert(&hash_table, "Hel World");
    insert(&hash_table, "GoodBye");
    insert(&hash_table, "GoodBye");
    insert(&hash_table, "wangbang");
    insert(&hash_table, "Holachola");
    insert(&hash_table, "antidis");

    printf("Test values inserted printing full hash_table...\n");
    //Print the list again 
    for(i=0;i<HASHTABLE_LENGTH;i++){
        print_ll(&(hash_table.table[i]));
    }
    //Deallocate memory
    freeHashTable(&hash_table);
}

void insert(struct Hashtable *h, char *str)
{
    int index = hash(str, h->length);

    if(h->table[index].string == NULL){         //if there is no string alrady stored in the array store the string there
        h->table[index].string = str;
    }else{                                  //conflicting indexes so create a new Node to branch off and store the string 
        insert_ll(&(h->table[index]), str);
    }
}

void insert_ll(struct Node *node, char *str)
{
    struct Node *index;
    
    for(index = node;index != NULL;index = index->next){
        if(strcmp(index->string, str) == 0) //if the string already exists in the linked list
            break;
        if(index->next == NULL){            //Otherwise traverse to the end and create a new Node to store the string
            index->next = newNode();
            index->next->string = str;
            break;
        }
    }
}

//Helper function for printing the values and memory locations of the hash table
void print_ll(struct Node *node)
{
    struct Node *index;
    for(index = node;index!=NULL;index = index->next){
        printf("memory_location: %p next: %p string: %s\t", index, index->next, index->string); 
    }
    putchar('\n');
}


void freeHashTable(struct Hashtable *h)
{
    int i;
    struct Node *index;
    //Iterate through the array and through the linked list at every index
    for(i=0;i<h->length;i++){
        for(index = h->table[i].next;index != NULL; index = index->next){
            free(index);
        }
    }
    free(h->table);
}

//Allocates an array of struct Node that is equal to the size of the hash table
void newHashTable(struct Hashtable *h, int size)
{
    int i;
    h->length = size;
    h->table = malloc(sizeof(struct Node) * size);
    memset(h->table, 0, sizeof(struct Node) *size);
}


struct Node* newNode()
{
    struct Node *ret_node = malloc(sizeof(struct Node));
    ret_node->string = NULL;
    ret_node->next = NULL;
    return ret_node;
}

//Very simple hash functions that makes no attempt to reduce collisions
int hash(char *str, int len)
{
    int i, sum = 0;
    for(i=0;i<strlen(str);i++){
        sum += str[i];
    }
    return sum % len;
}
