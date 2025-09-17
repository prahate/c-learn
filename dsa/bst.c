#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;

static node_t *root=NULL; // pointer to root node of tree

node_t * new_node(int data)
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    if (new) {
        new->data = data;
        new->left = NULL;
        new->right = NULL;
        return new;
    }
    return NULL;
}

void delete_node(node_t *n)
{
    if(n)
        free(n);
    n = NULL;
}


void insert(int data, node_t *rootnode)
{
    // case 1: is tree is empty or has no nodes
    if (root == NULL)
        root = new_node(data);
    else if (data < rootnode->data) {
        // case 2: insert to left subtree
    } 
    else if (data > rootnode->data) {
        // case 3: insert to right subtree
    }
}
