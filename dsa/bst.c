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

// level order traversal we need to use queue operation

// structure to hold node_t and next pointer
typedef struct sNode {
    node_t *node;
    struct sNode* next;
} Node_t;

Node_t* add_node(node_t *n)
{
    Node_t *new = (Node_t *)malloc(sizeof(Node_t));
    if (new) {
        new->node = n;
        new->next = NULL;
        return new;
    }
    return NULL;
}

void remove_node(Node_t *n)
{
    if(n)
    {
        free(n);
    }
    n = NULL;
}

// structure to hold head & tail of tree
typedef struct sQueue {
    Node_t *head;
    Node_t *tail;
} queue_t;

queue_t q;

bool isQEmpty()
{
    if (q.head == NULL && q.tail == NULL)
        return true;
    return false;
}

void enqueue(node_t *node)
{
    Node_t *new = add_node(node);
    // case 1: queue is empty
    if (q.head == NULL && q.tail == NULL)
    {
        q.head = new;
        q.tail = new;
    }
    // case 2: queue is not empty
    else {
        q.tail->next = new;
        q.tail = new;
    }
}

node_t* dequeue()
{
    // case 1: queue is empty
    if (q.head == NULL && q.tail == NULL)
    {
        printf("Queue is empty\n");
        return NULL;
    }
    // only one item in queue
    else if (q.head == q.tail) {
        node_t *tmp = q.head->node;
        //remove_node(q.head);
        q.head == NULL;
        q.tail == NULL;
        return tmp;
    }
    // case 2: queue is not empty
    else {
        Node_t *temp = q.head;
        node_t *tmp = q.head->node;
        q.head = temp->next;
        remove_node(temp);
        return tmp;
    }
}

void levelorder(node_t *rootnode)
{
    // first queue the root node
    enqueue(rootnode);

    while(!isQEmpty())
    {
        node_t *curr;
        // dequeue the node
        curr = dequeue();

        printf("%d ", curr->data);

        if (curr->left != NULL)
            enqueue(curr->left);

        if (curr->right != NULL)
            enqueue(curr->right);
    }
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
    printf("levelorder : ");
    levelorder(root);
    printf("\n");
    return 0;
}
