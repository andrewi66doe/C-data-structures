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
struct Node{
    char *string;
    struct Node *next;
};
struct Node* newNode();
struct Node* newHashTable(int size);
int hash(char *str, int len);
void insert(struct Node *node, char *str, int size);
void insert_ll(struct Node *node, char *str);
void freeHashTable(struct Node *table, int length);
void print_ll(struct Node *node);

int main(int argc, char **argv)
{
    int i;
    struct Node *hash_table = newHashTable(5);

    for(i=0;i<5;i++){
        print_ll(&hash_table[i]);
    }
    putchar('\n');
    insert(hash_table, "Hello World", 5);
    insert(hash_table, "Hello World", 5);
    insert(hash_table, "Hel World", 5);
    insert(hash_table, "GoodBye", 5);
    insert(hash_table, "GoodBye", 5);
    insert(hash_table, "wangbang", 5);
    insert(hash_table, "Holachola", 5);
    insert(hash_table, "antidis", 5);

    for(i=0;i<5;i++){
        print_ll(&hash_table[i]);
    }
    freeHashTable(hash_table, 5);
}

void insert(struct Node *node, char *str, int size)
{
    int index = hash(str, size);

    if(node[index].string == NULL){                     //if there is no string alrady stored in the array store the string there
        node[index].string = str;
    }else{                                              //conflicting indexes so create a new Node to branch off and store the string 
        insert_ll(&node[index], str);
    }
}

void insert_ll(struct Node *node, char *str)
{
    struct Node *index;
    
    for(index = node;index != NULL;index = index->next){
        if(strcmp(index->string, str) == 0)             //if the string already exists in the linked list
            break;
        if(index->next == NULL){                        //Otherwise traverse to the end and create a new Node to store the string
            index->next = newNode();
            index->next->string = str;
            break;
        }
    }
}
void print_ll(struct Node *node)
{
    struct Node *index;
    for(index = node;index!=NULL;index = index->next){
        printf("next: %p string: %s\t", index->next, index->string); 
    }
    putchar('\n');
}
void freeHashTable(struct Node *table, int length)
{
    int i;
    struct Node *index;
    for(i=0;i<length;i++){
        for(index = table[i].next;index != NULL; index = index->next){
            free(index);
        }
    }
    free(table);
}
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

int hash(char *str, int len)
{
    int i, sum = 0;
    for(i=0;i<strlen(str);i++){
        sum += str[i];
    }
    return sum % len;
}
