#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *str1="dusty";
char *str2="stody";

char charmap[26] = {0}; // to track frequency of chars

bool is_anagram(char *str1, char *str2)
{
    if (strlen(str1) != strlen(str2)) //if both strings dont have same lengths
        return false;

    int idx=0;
    int n= strlen(str1);
    for (int i=0; i < n; i++) // create map for each character which tracks its count
    {
        idx = str1[i]- 'a';
        charmap[idx]+=1;
    }
    
    idx=0;
    for(int j=0; j < n; j++)
    {
        idx = str2[j] - 'a';
        if (charmap[idx] == 0) // if no map does not contian char then return
            return false;
    }

    return true;
}

int main()
{
    printf("%s & %s are %sanagrams\n", str1, str2, is_anagram(str1, str2) ? " ":"not ");
}
