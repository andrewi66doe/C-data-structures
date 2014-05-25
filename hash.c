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


struct Node* newNode();
struct Node* newHashTable(int size);
int hash(char *str, int len);
void insert(struct Node node[], char *str, int size);
void insert_ll(struct Node *node, char *str);
void freeHashTable(struct Node table[], int length);
void print_ll(struct Node *node);


int main(int argc, char **argv)
{
    int i;
    //Allocate memory for a new hash table
    struct Node *hash_table = newHashTable(HASHTABLE_LENGTH);
    printf("New hash table containing no values\n");
    //Print the hash table containing no values
    for(i=0;i<HASHTABLE_LENGTH;i++){
        print_ll(&hash_table[i]);
    }
    putchar('\n');
    //Insert several values into the hash table
    insert(hash_table, "Hello World", 5);
    insert(hash_table, "Hello World", 5);
    insert(hash_table, "Hel World", 5);
    insert(hash_table, "GoodBye", 5);
    insert(hash_table, "GoodBye", 5);
    insert(hash_table, "wangbang", 5);
    insert(hash_table, "Holachola", 5);
    insert(hash_table, "antidis", 5);

    printf("Test values inserted printing full hash_table...\n");
    //Print the list again 
    for(i=0;i<HASHTABLE_LENGTH;i++){
        print_ll(&hash_table[i]);
    }
    //Deallocate memory
    freeHashTable(hash_table, HASHTABLE_LENGTH);
}

void insert(struct Node node[], char *str, int size)
{
    int index = hash(str, size);

    if(node[index].string == NULL){         //if there is no string alrady stored in the array store the string there
        node[index].string = str;
    }else{                                  //conflicting indexes so create a new Node to branch off and store the string 
        insert_ll(&node[index], str);
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


void freeHashTable(struct Node table[], int length)
{
    int i;
    struct Node *index;
    //Iterate through the array and through the linked list at every index
    for(i=0;i<length;i++){
        for(index = table[i].next;index != NULL; index = index->next){
            free(index);
        }
    }
    free(table);
}

//Allocates an array of struct Node that is equal to the size of the hash table
struct Node* newHashTable(int size)
{
    int i;

    struct Node *ret_table = malloc(sizeof(struct Node) * size);
    for(i=0;i<size;i++){
        ret_table->string = NULL;
        ret_table->next = NULL;
    }
    return ret_table;
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
