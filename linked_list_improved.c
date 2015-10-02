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
void reverse_ll(struct LinkedList *node);
void bubble_sort(struct LinkedList *node);

int main(int argc, char **argv)
{
    int i;

    struct LinkedList *list = newList();

    srand(time(NULL));

    for(i=0;i<20;i++)
        addNode(list, newNode(rand() % 50), true);

    puts("List of random values:");
    print_ll(list);
    puts("Reversing list:");
    reverse_ll(list);
    print_ll(list);
    puts("Sorting list:");
    bubble_sort(list);
    print_ll(list);

    freeListElements(list);
}

void print_ll(struct LinkedList *node)
{
        struct Node *index;
        for(index = node->head;index!=NULL;index = index->nextItem)
            printf("memory_location: %p next: %p value: %d\t\n", index, index->nextItem, index->data);
        putchar('\n');
}

/* Function: swaps nextItem and lastItem for a node struct */
void swap(struct Node *node)
{
    struct Node *temp;
    
    temp = node->nextItem;
    node->nextItem = node->lastItem;
    node->lastItem = temp;
}

void reverse_ll(struct LinkedList *node)
{
    struct Node *index;
    index = node->head; 
    //Swap nextItem and lastItem while traversing the list back to front
    while(index){
        swap(index);  
        if(index->lastItem == NULL)
            node->head = index;
        index = index->lastItem;
    }
}

void bubble_sort(struct LinkedList *node)
{
    int numswaps;
    struct Node *index;
    struct Node *p, *n, *nn;

    do{
        numswaps = 0;
        for(index=node->head;index!=NULL;index=index->nextItem){
            if(index->nextItem != NULL && index->nextItem->data < index->data){
               int temp = index->nextItem->data;
               index->nextItem->data = index->data;
               index->data = temp;

               numswaps++;
            }
        }
    }while(numswaps > 0);
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
    
    return list;
}


void freeListElements(struct LinkedList *list) 
{
    struct Node *index;
    for(index = list->head; index != NULL; index = index->nextItem)
        deleteNode(list, index);
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
        if(node->nextItem == NULL && node->lastItem == NULL){
            free(node);
            return 0;
        }else if(node->lastItem == NULL){
            node->nextItem->lastItem = NULL;
            list->head = node->nextItem;
        }else if(node->nextItem == NULL){
            node->lastItem->nextItem = NULL;
            list->current = node->lastItem;
        }else{
            node->lastItem->nextItem = node->nextItem;
            node->nextItem->lastItem = node->lastItem;
        }
        free(node);
        return 0;
    }
    return -1;
}

