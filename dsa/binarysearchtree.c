#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct tnode {
    int value;
    struct tnode *left;
    struct tnode *right;
} tnode_t;

static tnode_t *root = NULL; // pointer to root node of tree

tnode_t* new_node(int data)
{
    tnode_t *new = (tnode_t *)malloc(sizeof(tnode_t));
    if (new) {
        new->value = data;
        new->left = NULL;
        new->right = NULL;
        return new;
    }
    return NULL;
}

void delete_node(tnode_t *ptr)
{

    if(ptr) {
        free(ptr->left);
        free(ptr->right);
    }
    free (ptr);
}


void insert(tnode_t **rootptr, int data)
{
    tnode_t *root = *rootptr;
    // case 1: is tree is empty or has no nodes
    if (root == NULL)
        *rootptr =  new_node(data);
    else if (data < root->value) {
        // case 2: insert to left subtree
            insert(&root->left, data);
    }
    else if (data > root->value) {
        // case 3: insert to right subtree
            insert(&root->right, data);
    }
}

void remove_tnode(tnode_t** rootptr, int data)
{
    tnode_t *root = *rootptr;
    // find the element to remove
    //if (*rootptr == NULL)
    //    return;
    if (data < root->value)
        remove_tnode(&root->left, data);
    else if (data > root->value)
        remove_tnode(&root->right, data);
    else
    {
        // case 1: node has no subtrees ie. leaf node
        if (root->left == NULL && root->right == NULL)
        {
            //*(&root) = NULL;
            free(*(&root));
        }
        // case 2 & 3: node has right or left subtree
        else if (root->left == NULL)
        {
            tnode_t *temp = root->right;
            root = temp;
            delete_node(root);
        }
        else if (root->right == NULL)
        {
            tnode_t *temp = root->left;
            root = temp;
            delete_node(root);
        }
        // case 4: node has both left & right subtree, choose min from right subtree
        //          or choose maximum from left subtree
    }
}

void inorder(tnode_t *rootptr)
{
    if (rootptr == NULL)
        return;
    if (rootptr->left != NULL)
        inorder(rootptr->left);
    if (rootptr->value)
        printf("%d ", rootptr->value);
    if (rootptr->right != NULL)
        inorder(rootptr->right);
}


void preorder(tnode_t *rootptr)
{
    if (rootptr == NULL)
        return;
    if (rootptr->value)
        printf("%d ", rootptr->value);
    preorder(rootptr->left);
    preorder(rootptr->right);
}

void postorder(tnode_t *rootptr)
{
    if(rootptr == NULL)
        return;

    postorder(rootptr->left);
    postorder(rootptr->right);
    if (rootptr->value)
        printf("%d ", rootptr->value);
}

#if 0
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
#endif

int main()
{
    insert(&root, 11);
    insert(&root, 6);
    insert(&root, 15);
    insert(&root, 3);
    insert(&root, 8);
    insert(&root, 13);
    insert(&root, 17);
    insert(&root, 1);
    insert(&root, 5);
    insert(&root, 7);
    insert(&root, 12);
    insert(&root, 14);
    insert(&root, 19);

    printf("Inorder : ");
    inorder(root);
    printf("\n");
#if 1
    printf("Preorder : ");
    preorder(root);
    printf("\n");
    printf("Postorder : ");
    postorder(root);
    printf("\n");
#endif

    //printf("levelorder : ");
    //levelorder(root);
    //printf("\n");
#if 1
    remove_tnode(&root, 5);
    printf("Inorder : ");
    inorder(root);
    printf("\n");

    remove_tnode(&root, 7);
    printf("Inorder : ");
    inorder(root);
    printf("\n");

    remove_tnode(&root, 19);
    printf("Inorder : ");
    inorder(root);
    printf("\n");
#endif
    
    return 0;
}
