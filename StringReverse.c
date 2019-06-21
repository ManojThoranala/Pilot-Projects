/***************************************************************
*Program to reverse the string 
**********************************************************/

/***************************************************************
*ALGORITHM:
        1. Accepts the string from the user.
        2. The function reverse_string reverses the string by tranferring values from end to first into the new string
        3. At end append null value to string.
**********************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int string_reverse (char * str, char * reversed_str)
{  
    int str_len = 0;
    char * ch = str;
    while(* ch++ != '\n') str_len++;
    ch = reversed_str;
    for (int i = str_len - 1; i >= 0; i--, ch++){
		* ch = str[i];
    }
    ch[1] = '\0';
	return 0;
}

void main()
{
	char * string;
	char * string_reversed;
	string = malloc(256 * sizeof(char));
	string_reversed = malloc(256 * sizeof(char));
    while(1){
        memset(string, 0, sizeof(char)*256);
        printf("Enter the string to make reverse: Type quit to exit\n");
        if (fgets(string, 256, stdin) == 0)
            break;
        if (strncmp(string, "quit", 4) == 0)
            break;
        string_reverse(string, string_reversed);
        printf("Here is the reversed string:\n");
        printf("%s\n", string_reversed);
    }
    free(string);
}

/********************************************************************************************/
/**********************************************************
*Program to reverse the string - Optimized
**********************************************************/

/***************************************************************
*ALGORITHM:
        1. Accepts the string from the user.
        2. The function reverse_string reverses the string by swapping the values while traversing till the middle of the string
        3. At end append null value to string.
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int string_revese(char *str)
{
    int str_len = 0;
    char *ch = str;
    char temp;
    while (*ch != '\n')
    {
        str_len++;
        ch++;
    }
    ch--;
    for (int i = 0; i <= str_len / 2; i++, ch--)
    {
        temp = *ch;
        *ch = str[i];
        str[i] = temp;
    }
    return 0;
}

int string_reverse_xor(char *str)
{
    int str_len = 0;
    char *ch = str;
    while (*ch != '\n')
    {
        str_len++;
        ch++;
    }
    for (int i = 0; i < str_len / 2; i++)
    {
        str[i] = str[i] ^ str[str_len - 1 - i];
        str[str_len - 1 - i] = str[i] ^ str[str_len - 1 - i];
        str[i] = str[i] ^ str[str_len - 1 - i];
    }
}

void main()
{
    char *string;
    string = malloc(256 * sizeof(char));
    while (1)
    {
        memset(string, 0, sizeof(char) * 256);
        printf("Enter the string to make reverse: Type quit to exit\n");
        if (fgets(string, 256, stdin) == 0)
            break;
        if (strncmp(string, "quit", 4) == 0)
            break;
        string_revese(string);
        printf("Here is the reversed string: Using temp variable and no extra array\n");
        printf("%s\n", string);
        string_reverse_xor(string);
        printf("Here is the reversed string: Using xor operation and no temp variable and no extra array\n");
        printf("%s\n", string);
    }
    free(string);
}

