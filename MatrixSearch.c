/**************************************************
*Program to search pxp matrix in mxn matrix, 
whose sum of the elements is equal to the sum given by user.
/**************************************************/
/**********************************************
ALGORITHM:
        1. Accepts the mxn matrix in string format "[a b; c d]" and validates and parses it to normal 2d array
        2. Matrix search funtion is called from main to iterate through the given mxn matrix and
         finds the pxp matrix whose elements sum up to the sum given by user
        3. Funtion at step 2 has four for loops to compute the pxp elements sum in a mxn matrix
        4. if the sum value matches then it prints the matrix and it's base index
/**********************************************/

/******************************************************************
Program for providing calculator operations.
*******************************************************************
*File Name : MatrixSearch.c
*Date : 14/06/2019
*Author : Manoj T M
*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rows = 1;
int columns = 0;
double *matrix_arr;
double **matrix;
int search_matrix_size = 2;

/*************************************************
 * Fucntion to search pxp matrix whose elements sum up to the sum value given by user
 * ***********************************************/
int matrix_search(double sum)
{
    int index = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix[i][j] = matrix_arr[index];
            index++;
        }
    }
    double matrix_sum = 0;
    for (int i = 0; i <= rows - search_matrix_size; i++)
    {
        for (int j = 0; j <= columns - search_matrix_size; j++)
        {
            matrix_sum = 0;
            for (int k = i; k < i + search_matrix_size; k++)
            {
                for (int l = j; l < j + search_matrix_size; l++)
                {
                    matrix_sum += matrix[k][l];
                }
            }

            if (sum == matrix_sum)
            {
                printf("The Matrix with sum value found at index %d%d:\n[", i, j);
                for (int k = i; k < i + search_matrix_size; k++)
                {
                    for (int l = j; l < j + search_matrix_size; l++)
                    {
                        printf("%.3lf\t", matrix[k][l]);
                    }
                    printf("\n");
                }
                printf("]\n");
            }
        }
    }
}

/******************************************************
/validate a digit
******************************************************/

int is_digit(char p)
{
    if (p >= '0' && p <= '9' || p == '.')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/****************Function to validate right square brace******************/
int is_right_sq(char p)
{
    if (p == ']')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**************Function to validate left square brace****************/

int is_left_sq(char p)
{
    if (p == '[')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*****************Funtion to validate matrix which is in string input*******************/

int validate_matrix(char *matrix)
{
    int left_sq = 0, right_sq = 0;
    int error = 0;
    for (int i = 0; *matrix != '\n'; i++, matrix++)
    {
        if (*matrix == ']' && left_sq == 0)
        {
            error = 1;
            printf("Invalid Matrix: Right Square Brace found before left one\n");
            return 1;
        }
        if (is_left_sq(*matrix))
        {
            left_sq++;
        }
        if (is_right_sq(*matrix))
        {
            right_sq++;
        }
        if (!is_digit(*matrix) && !is_left_sq(*matrix) && !is_right_sq(*matrix) && *matrix != ' ' && *matrix != ';')
        {
            error = 1;
            printf("Invalid Matrix: Found Unsupported Characters in Matrix.\n");
            return 1;
        }
    }
    if (left_sq != right_sq){
        error = 1;
        printf("Invalid Matrtix: Square Braces Mismatch.\n");
        return 1;
    }
    return error;
}

/****************Function to parse the string to matrx format****************/
int parse_matrix(char *matrix)
{
    double * arr_ptr = matrix_arr;
    int column_check_count = 0;
    char * ori_num_ptr, *num_ptr = malloc(10 * sizeof(char));
    ori_num_ptr = num_ptr;
    if (is_left_sq(*matrix))
    {
        matrix++;
        while (!is_right_sq(*matrix))
        {
            if (is_digit(*matrix))
            {
                memset(num_ptr, 0, sizeof(char) * 10);
                num_ptr = ori_num_ptr;
                while (is_digit(*matrix))
                {
                    *num_ptr = *matrix;
                    if (is_digit(*(matrix + 1)))
                    {
                        num_ptr++;
                        matrix++;
                    }
                    else
                        break;
                }
                *(num_ptr + 1) = '\0';
                *arr_ptr = atof(ori_num_ptr);
                arr_ptr++;
                if (rows == 1)
                {
                    columns++;
                }
                column_check_count++;
            }
            else if (* matrix == ' ')
            {
                ;
            }
            else if (* matrix == ';')
            {
                if (is_right_sq(* (matrix + 1))){
                    printf("Invalid Matrix: Found an extra ';' at end.\n");
                    return 0;
                }
                rows++;
                if (rows > 1){
                    if (column_check_count == columns)
                    {
                        column_check_count = 0;
                    }
                    else
                    {
                        printf("Invlaid Matrix: Columns are not same across rows.\n");
                        return 0;
                    }
                }
            }
            matrix++;
        }
        if (column_check_count == columns)
        {
            column_check_count = 0;
        }
        else
        {
            printf("Invlaid Matrix: Columns are not same across rows.\n");
            return 0;
        }
    }
    free(num_ptr);
    return 1;
}

/*******************Main*********************/
void main()
{
    char *matrix_str;
    double sum;
    char nl;
    int infinite = 0;
    matrix_arr = malloc(256 * sizeof(double));
    matrix_str = malloc(256 * sizeof(char));
    double * mat_arr_ptr = matrix_arr;
    char * str_ptr = matrix_str;
    while (1)
    {
        if (infinite > 5){
            printf("Program Crashing: Infinite Loop");
            infinite = 0;
            break;
        }
        rows = 1;
        columns = 0;
        matrix_arr = mat_arr_ptr;
        matrix_str = str_ptr;
        printf("\n\nThe input format for matrix is [a b c; d e f; g h i].\nPlease give space between two numbers.\nRows are Separated by semicolons and columns by spaces. Type quit to exit\n");
        printf(">>\n");
        printf("Enter Required Matrix:\n");
        if (fgets(matrix_str, 256, stdin) == 0)
            break;
        if (strncmp(matrix_str, "quit", 4) == 0)
            break;
        printf("Enter the sum value to serach pxp matrix:\n");
        int sum_check = scanf("%lf%c", &sum, &nl);
        if (nl != '\n'){
            infinite++;
            printf("1%c", nl);
            continue;
        }
        printf("Enter the value for p in pxp matrix:\n");
        nl = ' ';
        int n_check = scanf("%d%c", &search_matrix_size, &nl);
        if (nl != '\n'){
            infinite++;
            printf("2%c", nl);
            continue;
        }
        int error = validate_matrix(matrix_str);
        if (!error)
        {
            int check = parse_matrix(matrix_str);
            if (check)
            {
                printf("Input given is %d x %d Matrix\n", rows, columns);
                matrix = malloc(rows * sizeof(double *));
                for (int i = 0; i < rows; i++)
                {
                    matrix[i] = malloc(columns * sizeof(double));
                }
                matrix_search(sum);
            }
            else
            {
                printf("Error in Parsing Matrix Input. Try Again.\n");
                infinite++;
                continue;
            }
        }
        else
        {
            printf("Error in Validating Matrix Input. Try Again.\n");
            infinite++;
            continue;
        }
    }
    free(matrix_str);
}

