
/*******************************************************************
*Program for counting the number of bit changes between two numbers.
********************************************************************/


/******************************************************************
Algorithm:
1. Accept numbers to compared from the user and validate for proper number format.
2. Perform xor operation on given two numbers.
3. Count the numbers bits set in the xor'ed result-(from step 2).
4. Print the count and it's the numbers of bit changes between two given numbers.
********************************************************************/

/*******************************************************************
*File Name : BitChange.c
*Date : 17/06/2019
*Author : Manoj T M
*******************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*******************************************************************
*Function to count the number of bit changes between two numbers
*and returns count of type integer
*******************************************************************/

int bit_change_count(int num1, int num2){
    int diff = 0;
    int count = 0;
    // xor operation gives the dissimilar bits at all bit positions in the number
    diff = num1 ^ num2;
    //looping to find the number of bits set in the xor'ed result. counting from right to left till it finishes set bit positons in xor'ed result
    for (unsigned int bit = 1; bit <= diff && bit > 0; bit <<= 1){
        if (diff & bit){
            count++;
        }
    }
    return count;
}

/*******************************************************
*Main Function
********************************************************/
void main ()
{
    int n1, n2, check_if_number;
    char in[256];
    char nl;
    // using the while loop below for input validation and repeats the propmt for wrong input.
    while (1){
        printf("Enter the number1:\n");
        fgets(in, 256, stdin);
        check_if_number = sscanf(in, "%d%c",  &n1, &nl);
        //checking whether the character present is only '\n' after retrieving integer
        if (nl != '\n'){
            check_if_number = 0;
        }
        //validating the input using scanf return value
        if (!check_if_number){
            printf("Entered input 1 is not a number. Try Again.\n");
            continue;
        }

        else break;
    }
    nl = ' ';
    while(1){
        printf("Enter the number2:\n");
        fgets(in, 256, stdin);
        check_if_number = sscanf(in, "%d%c", &n2, &nl);
        if (nl != '\n'){
            check_if_number = 0;
        }

        if (!check_if_number){
            printf("Entered input 2 is not a number. Try Again.\n");
            continue;
        }

        else break;
    }

    printf("\nThe number of bit changes between numbers given is '%d' bits\n", bit_change_count(n1, n2));
}
