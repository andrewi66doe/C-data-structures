/*
 * =====================================================================================
 *
 *       Filename:  binary_tree.c
 *
 *    Description:  Implementation of a binary tree
 *
 *        Version:  1.0
 *        Created:  02/04/14 10:02:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andrew Walker (), andrewg.walker@outlook.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


struct Node{
    struct Node *parent;
    struct Node *node_r;
    struct Node *node_l;
    int data;
};

struct Node* newNode(int value);
void destroyTree(struct Node *tree);

static int lookup(struct Node *node, int value);
void insert(struct Node *node, int value);

int main(int argc, char **argv)
{
    int i;
    int values[] = {11,6,8,19,4,10,5,17,43,49,31};
    struct Node *root = newNode(20);
    for(i=0;i<11;i++)
        insert(root, values[i]);
        
    destroyTree(root);
    
}

struct Node* newNode(int value)
{
    struct Node *ret_node = malloc(sizeof(struct Node));
    ret_node->parent = NULL;
    ret_node->node_r = NULL;
    ret_node->node_l = NULL;
    ret_node->data = value;
    return ret_node;
}

void destroyTree(struct Node *tree)
{
    if(tree != NULL){
        destroyTree(tree->node_l);
        destroyTree(tree->node_r);
        printf("Deleting node %d\n", tree->data);
        free(tree);
    }
}

void insert(struct Node *node, int value)
{
    if(node->data > value){
        if(node->node_l == NULL){
            node->node_l = newNode(value);
            node->node_l->parent = node;
        }
        else
            insert(node->node_l, value);
    }
    else if(node->data < value){
        if(node->node_r == NULL){
            node->node_r = newNode(value);
            node->node_r->parent = node;
        }
        else
            insert(node->node_r, value);
    }
}

void deleteNode(struct Node *node)
{
    if(node->node_r == NULL){                   //Case with only left node
        node->node_l->parent = node->parent;
        node->parent = NULL;
        free(node);
    }else if(node->node_l == NULL){             //Case with only right node
        node->node_r->parent = node->parent;
        node->parent = NULL;
        free(node);
    }else{                                      //Case with both nodes
        node->data = node->node_l->data;
        node->node_l = node->node_l->node_l;
        node->node_r = node->node_l->node_r;
        
    }
       
}
static int lookup(struct Node *node, int value)
{
    if(node == NULL)
        return false;

    if(node->data == value)
        return true;
    else{
        if(value < node->data)
            return lookup(node->node_l, value);
        else
            return lookup(node->node_r, value);
    }
}
