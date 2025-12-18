#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *str1="abcdeabc";
char *str2="deab";

bool is_substring(char *str1, char *substr)
{
    if (strlen(substr) > strlen(str1)) // if substr is larger then false
        return false;
    int i=0;
    for (i=0; i <strlen(str1); i++)
    {
        if (substr[0] == str1[i])
            break;
    }
    
    if (i == strlen(str1))
        return false;
    else if ((strlen(str1) - i) < strlen(substr))
        return false;
    
    i++;
    for(int j=1; j < strlen(substr); j++, i++)
    {
        if (substr[j] != str1[i])
            return false;
    }

    return true;
}

int main()
{
    printf("%s does%scontain substring %s\n", str1, is_substring(str1, str2) ? " ": " not ", str2);
}
