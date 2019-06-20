/***************************************************************
*
**********************************************************/


#include <stdio.h>
#include <stdlib.h>

int string_revese (char * str, char * reversed_str)
{  
    int str_len = 0;
    char * ch = str;
    while(* ch++ != '\n') str_len++;
    for (int i = str_len - 1; i < = 0; i--, reversed_str++){
		* reversed_str = str[i];
    }
    reversed_str[1] = '\n';
    reversed_str[2] = '\0';
	return 0;
}

void mian()
{
	char * string;
	char * string_reversed;
	string = malloc(256 * sizeof(char));
	string_reversed = malloc(256 * sizeof(char));
	printf("Enter the string to make reverse:\n");
	fgets(string, 256, stdin);
	string_reverse(string);
	printf("Here is the reversed string\n");
	printf("%s", string_reversed);
}


/***********************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int string_revese (char * str)
{  
    int str_len = 0;
    char * ch = str;
	char temp;
    while(* ch++ != '\n') str_len++;
	ch--;
    for (int i = 0; i <= (str_len - 1) / 2; i++, ch--){
		temp = * ch;
		* ch = str[i];
		str[i] = temp;
    }
	return 0;
}

int string_reverse_xor (char * str)
{
	int str_len = 0;
    char * ch = str;
    while(* ch++ != '\n') str_len++;
	for (int i = 0; i <= (str_len - 1) / 2; i++){
		str[i] = str[i] ^ str[str_len-1-i];
		str[i] = str[i] ^ str[str_len-1-i];
		str[str_len-1-i] = str[i] ^ str[str_len-1-i];
	}
}

void main()
{
	char * string;
	string = malloc(256 * sizeof(char));
	printf("Enter the string to make reverse:\n");
	fgets(string, 256, stdin);
	string_reverse(string);
	printf("Here is the reversed string\n");
	printf("%s", string);
}
