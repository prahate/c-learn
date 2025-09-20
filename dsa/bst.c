#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;

static node_t *root; // pointer to root node of tree

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


node_t* insert(node_t *rootnode, int data)
{
    // case 1: is tree is empty or has no nodes
    if (rootnode == NULL)
        return new_node(data);
    else if (data < rootnode->data) {
        // case 2: insert to left subtree
        if ( rootnode->left == NULL)
            rootnode->left = new_node(data);
        else
            insert(rootnode->left, data);
    }
    else if (data > rootnode->data) {
        // case 3: insert to right subtree
        if (rootnode->right == NULL)
            rootnode->right = new_node(data);
        else
            insert(rootnode->right, data);
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
    root = insert(NULL, 11);
    insert(root, 6);
    insert(root, 15);
    insert(root, 3);
    insert(root, 8);
    insert(root, 13);
    insert(root, 17);
    insert(root, 1);
    insert(root, 5);
    insert(root, 12);
    insert(root, 14);
    insert(root, 19);

    printf("Inorder : ");
    inorder(root);
    printf("\n");
    printf("Preorder : ");
    preorder(root);
    printf("\n");
    printf("Postorder : ");
    postorder(root);
    printf("\n");
    return 0;
}
