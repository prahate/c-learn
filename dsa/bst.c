#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;

static node_t root; // pointer to root node of tree

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
    if (rootnode == NULL)
        rootnode = new_node(data);
    else if (data < rootnode->data) {
        // case 2: insert to left subtree
        if ( rootnode->left == NULL)
            rootnode->left = new_node(data);
        else
            insert(data, rootnode->left);
    }
    else if (data > rootnode->data) {
        // case 3: insert to right subtree
        if (rootnode->right == NULL)
            rootnode->right = new_node(data);
        else
            insert(data, rootnode->right);
    }
}

void inorder(node_t *rootnode)
{
    if (rootnode == NULL)
        return;
    inorder(rootnode->left);
    if (rootnode->data)
        printf("%d ", rootnode->data);
    inorder(rootnode->right);
}

void preorder(node_t *rootnode)
{
    if (rootnode == NULL)
        return;
    if (rootnode->data)
        printf("%d ", rootnode->data);
    preorder(rootnode->left);
    preorder(rootnode->right);
}

void postorder(node_t *rootnode)
{
    if(rootnode == NULL)
        return;

    postorder(rootnode->left);
    postorder(rootnode->right);
    if (rootnode->data)
        printf("%d ", rootnode->data);
}

int main()
{
    insert(11, &root);
    insert(6, &root);
    insert(15, &root);
    insert(3, &root);
    insert(8, &root);
    insert(13, &root);
    insert(17, &root);
    insert(1, &root);
    insert(5, &root);
    insert(12, &root);
    insert(14, &root);
    insert(19, &root);

    printf("Inorder : ");
    inorder(&root);
    printf("\n");
    printf("Preorder : ");
    preorder(&root);
    printf("\n");
    printf("Postorder : ");
    postorder(&root);
    printf("\n");
    return 0;
}
