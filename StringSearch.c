/**********************************************
*Program to search a string pattern in the given input string
***********************************************/

/**********************************************
*ALGORITHM:
        1. Accept the string and pattern string to be serached from the user
        2. Count the number of characters in the Pattern using for loop unitl it reaches '\n' in the strings
        3. For loop to iterate through each element in the given string
        4. one more for loop inside the loop at step 3 to iterate the pattern string and condition for loop is to have the
***********************************************/

#include <stdio.h>
#include <stdlib.h>

/*******************************************************
*String Search
********************************************************/
int str_index[256];
int occ_count = 0;
int string_search (char * search_str, char * string)
{
    int index = 0;
    int count = -1;
    int pat_count = 0;
    char * str = string;
    printf("Searching The Pattern.");
    printf(".");
    char * pat_str = search_str;
    while (* pat_str++ != '\n') pat_count++;
    for(int i=0; * string != '\n'; i++, string++){
        printf(".");
        count = pat_count;
        str = string;
        for(pat_str=search_str; * str == * pat_str && * pat_str != '\n'; pat_str++, str++){
            count--;
            if (count == 0){
                str_index[index] = i + 1;
                index++;
                occ_count++;
            }
        }
    }
    if (occ_count) return pat_count;
    else return 0;
}

/************************************************************
*Main Function
*************************************************************/
void main ()
{
    char * in;
    in = (char *) malloc(256*sizeof(char));
    char * pattern;
    pattern = (char *) malloc(256*sizeof(char));
    printf("Enter the Source String:\n");
    fgets(in, 256, stdin);
    printf("Enter the pattern string to search:\n");
    fgets(pattern, 256, stdin);
    int check_count = string_search(pattern, in);
    if (check_count){
        printf("\nTotal number of pattern occurances: %d\n", occ_count);
        for(int i=0; i < occ_count; i++){
            printf("\nPattern found in the string at positions -- %d to %d --", str_index[i], str_index[i] + check_count - 1);
        }
        printf("\n");
    }
    else printf("\nNo Patterns found in the given strings\n");
}
