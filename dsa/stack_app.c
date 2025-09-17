#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<string.h>

/*
The one of the application of stack is in matching brackets
e.g. ([{}]) is valid
     [[{]] is invalid
Now using stack we will implement this logic to check for valid
bracket sequence
*/

typedef struct node {
    char c;
    struct node *next;
} node_t;

node_t* new_node(char c)
{
    node_t *new = (node_t *)malloc(sizeof(node_t));
    if (new)
    {
        new->c = c;
        new->next = NULL;
    }
    return new;
}

void delete_node(node_t *n)
{
    if (n) {
        free(n);
        n=NULL;
    }
}

node_t *top = NULL; // pointer to top of stack

void push(char c)
{
    node_t *n = new_node(c);
    if (top == NULL) {
        top = n;
        n->next = NULL;
    } else {
        n->next = top;
        top = n;
    }
}

char pop()
{
    char ret;
    if(top == NULL)
        printf("Stack is empty\n");
    else {
        node_t *temp = top;
        ret = top->c;
        top = temp->next;
        delete_node(temp);
    }

    return ret;
}

bool isEmpty()
{
    if (top == NULL)
        return true;
    return false;
}

bool isLeftSideBracket(char *c)
{
    if (*c == '[' || *c == '{' || *c == '(')
        return true;
    return false;
}

char reversedBracket(char *c)
{
    if (*c == '[')
        return ']';
    else if (*c == '{')
        return '}';
    else if (*c == '(')
        return ')';
}


bool validateSequence(char *s, int len)
{
    for(int i=0; i < strlen((const char *)s); i++)
    {
        char curr = *(s+i);
        if (isLeftSideBracket((s+i)))
            push(*(s+i));
        else {
            if (isEmpty())
                return false;
            char tos = pop();
            if (curr != reversedBracket(&tos))
                return false;
        }
    }
    return isEmpty();
}


int main() {
    char s1[] = {'{','[','(',')',']','}'};
    int len = strlen(s1);

    if (validateSequence(s1, len))
        printf("s1 Valid sequence\n");
    else
        printf("s1 Invalid sequence\n");
    
    char s2[] = {'{','[','(',')',']','{', '}'};
    len = strlen(s2);

    if (validateSequence(s2, len))
        printf("s2 Valid sequence\n");
    else
        printf("s2 Invalid sequence\n");
    
    char s3[] = {'{',']'};
    len = strlen(s3);

    if (validateSequence(s3, len))
        printf("s3 Valid sequence\n");
    else
        printf("s3 Invalid sequence\n");
    
    pop(); // to pop out last failed push item
    char s4[] = {'{','}','(',')','[','(', ')', ']'};
    int len2 = strlen(s4);

    if (validateSequence(s4, len2))
        printf("s4 Valid sequence\n");
    else
        printf("s4 Invalid sequence\n");
}
