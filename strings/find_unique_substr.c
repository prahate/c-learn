#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char *str = "armaandutt";
//char *str = "edpresso";
//char *str = "pwwkew";
//char *str="bbbbbbb";

char charmap[26] = {0}; // to track characters with their index in string
int currlen=0; // to track current max length
int maxlen=0; // to track max string

void find_unique_substr(char *str)
{
    int i=0, j=0; //i tracks start and j tracks end

    char *ans; // alternate to hold unique string
    ans = (char *)malloc(sizeof(char)*strlen(str));

    while(j < strlen(str))
    {
        int mapidx = str[j] - 'a'; //get idex for charater to store its postion in array
        if (charmap[mapidx] == 0) {  // it means character is not repeated, increment j
            charmap[mapidx] = j + 1;
        }
        else {
            i = charmap[mapidx];    // update i to previous occurance of character
            charmap[mapidx] = j+ 1; // update charmap with new position of repeated char 
        }

        currlen = j -i + 1;
        if (currlen > maxlen) {
            maxlen = currlen;
            strncpy(ans, (str + i), j-i + 1); // copy the maxlen string to an
        }
        j++;

    }
    printf("Unique substring is %s\n", ans);
    free(ans);
}


int main()
{
    printf("Input string is %s\n", str);
    find_unique_substr(str);
    return 0;
}
