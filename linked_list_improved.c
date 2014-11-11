/*
 * =====================================================================================
 *
 *       Filename:  linked_list_improved.c
 *
 *    Description:  A linked list 
 *
 *        Version:  1.0
 *        Created:  02/01/14 21:22:51
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
#include <stdbool.h>

struct Node
{
    struct Node *lastItem;
    int data;
    struct Node *nextItem;
};

struct LinkedList
{
    struct Node *head;
    struct Node *current;
};

void freeListElements(struct LinkedList *list);
struct LinkedList* newList();
struct Node* newNode(int value);
struct Node* searchList(struct LinkedList *list, int value);
void addNode(struct LinkedList *list, struct Node *node, bool at_end);
int deleteNode(struct LinkedList *list, struct Node *node);
void print_ll(struct LinkedList *node);


int main(int argc, char **argv)
{
    int i;

    struct LinkedList *list = newList();

    for(i=0;i<20;i++){
        addNode(list, newNode(i), true);
    }
    print_ll(list);

    freeListElements(list);
}

void print_ll(struct LinkedList *node)
{
        struct Node *index;
        for(index = node->head;index!=NULL;index = index->nextItem){
            printf("memory_location: %p next: %p value: %d\t", index, index->nextItem, index->data);
            putchar('\n');
        }
        putchar('\n');
}

struct Node* newNode(int value)
{
    struct Node *root = malloc(sizeof(struct Node));
    root->lastItem = NULL;
    root->nextItem = NULL;
    root->data = value;

    return root;
}


struct LinkedList* newList()
{
    struct LinkedList *list = malloc(sizeof(struct LinkedList));
    list->head = NULL;
    list->current = NULL;
}


void freeListElements(struct LinkedList *list) 
{
    struct Node *index;
    for(index = list->head; index != NULL; index = index->nextItem){
        deleteNode(list, index);
    }
    free(list);
}

struct Node* searchList(struct LinkedList *list, int value)
{
    struct Node *index = list->head;
    for(index;index != NULL; index = index->nextItem){
        if(index->data == value)
            return index;
    }
    return NULL;
}

void addNode(struct LinkedList *list, struct Node *node, bool at_end)
{
   if(list->head == NULL){                                                  //If the list has no elements set node to be the head and current node
       list->head = node;
       list->current = node;
       return;
   }
   if(at_end){
       node->nextItem = NULL;
       node->lastItem = list->current;
       list->current->nextItem = node;
       list->current = node;
   }else{
       node->lastItem = NULL;
       node->nextItem = list->head;
       list->head->lastItem = node;
       list->head = node;
   }
}

int deleteNode(struct LinkedList *list, struct Node *node)
{
    if(node != NULL){
        if(node->nextItem == NULL && node->lastItem == NULL){               //If the list has only one element just free that element and return
            free(node);
            return 0;
        }else if(node->lastItem == NULL){                                   //If at the beginning of the list 
            node->nextItem->lastItem = NULL;
            list->head = node->nextItem;
        }else if(node->nextItem == NULL){                                   //If at the end of the list
            node->lastItem->nextItem = NULL;
            list->current = node->lastItem;
        }else{                                                              //If anywhere else in the list
            node->lastItem->nextItem = node->nextItem;
            node->nextItem->lastItem = node->lastItem;
        }
        free(node);                                                         //free the node struct
        return 0;
    }else{
        return -1;
    }
}



