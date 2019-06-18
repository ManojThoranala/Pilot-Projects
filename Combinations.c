/******************************************************
*Program to find the 2 digit non repeated
*combibations of an given integer.
*******************************************************/

/******************************************************
Algorithm:
1. Accept the input from the user and valiadte for number
2. Place the indivisual digits of the number in an array
3. Create 2D array for 2 digit space.
4. Iterate the array using for loop till its length (use two for loops for two digits)
5. write an if condition to eliminate the same digits in the number combination found like 33, 22, 44, 11 ... and to avoid combinations like 		   01, 05 ...
6. Assign value '1' to the combination already found. example: if combination is 23 then >> "two_d_arr[2][3] = 1" to avoid duplication.
7. Print the combination inside the if condition described in step 6 present in inner for loop seen in step 4.
*******************************************************/


/******************************************************
*File Name : assignment_1_2.c
*Date : 17/06/2019
*Author : Manoj T M
*Org : PathPartner Technology
*******************************************************/

#include <stdio.h>
#include <ctype.h>

/******************************************************
*Fuction to print all the combinations for given number
*******************************************************/

void print_combinations(int *data, int r, int arr_length){
    int data_set[10][10] = {0};
    for(int i=0; i <= arr_length; i++){
        for(int j=0; j <=arr_length; j++){
            if (i != j && data[i] != data[j] && data_set[data[i]][data[j]] != 1 && data[i] != 0){
                //2d_array for storing the number combination found and assign value 1.
                data_set[data[i]][data[j]] = 1;
                //printing the combination
                printf("%d%d", data[i], data[j]);
                printf("\n");
            }
        }
    }
}

/****************************************************
*Main Function
*****************************************************/

void main ()
{
    int number;
    int place_val = 1;
    int digit_arr[10];
    int index = 0;
    int digits = 2;
    int check_if_number = 0;
    char in[256];
    char nl;
    while(1){
        //loop to validate the given input for a number and prompting the user aggain if the input is not feasible.
        printf("Enter the 3 digit integer to find its 2 digit combinations:\n");
        fgets(in, 256, stdin);
        check_if_number = sscanf(in, "%d%c", &number, &nl);
        if (number < 0){
            printf("Entered input is a negative number.\nAbsolute value of the gievn number is considered.\n");
            number = number * (-1);
        }
        if(number > 0 && number < 100){
            printf("Entered input is a two digit number. Try Again.\n");
            continue;
        }
        if (nl != '\n'){
            check_if_number = 0;
        }
        if (!check_if_number){
            printf("Entered input is not a number. Try Again.\n");
            continue;
        }
        else break;
    }
    while(number){
        place_val = (index + 1) * 10;
        digit_arr[index] = number % 10;
        number = number / 10;
        index += 1;
    }
    print_combinations(digit_arr, digits, index-1);
}
