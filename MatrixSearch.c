/**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rows = 1;
int columns = 0;
double * matrix_arr;
double ** matrix;
int size = 2;

int matrix_search(double sum)
{
    int index = 0;
    for (int i= 0; i < rows; i++){
        for (int j= 0; j < columns; j++){
            matrix[i][j] = matrix_arr[index];
            printf("%lf", matrix_arr[index]);
            index++;
        }
    }
    double matrix_sum = 0;
    for (int i= 0; i <= rows - size; i++){
        for (int j= 0; j <= columns - size; j++){
            matrix_sum = 0;
            for (int k = i; k < i + size; k++){
                for (int l = j; l < j + size; l++){
                    matrix_sum += matrix[k][l];
                }
            }
            
            if (sum == matrix_sum){
                printf("The Matrix with sum value found at index %d%d:\n[", i,j);
                for (int k = i; k < i + size; k++){
                    for (int l = j; l < j + size; l++){
                        printf("%.0lf\t",matrix[k][l]);
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
    if (p >= '0' && p <= '9' || p == '.'){
    return 1;
    }
    else{ 
        return 0;
    }
}

/**********************************************/
int is_right_sq(char p)
{
    if (p == ']'){
        return 1;
    }
    else{
        return 0;
    }
}

/****************************************/

int is_left_sq(char p)
{
    if (p == '['){
        return 1;
    }
    else{
        return 0;
    }
}
/******************************************* */

int validate_matrix(char * matrix)
{
    int left_sq = 0, right_sq = 0;
    int error = 0;
    for (int i=0; * matrix != '\n'; i++, matrix++){
        if (* matrix == ']' && left_sq == 0){
            error = 1;
            printf("Invalid Matrix: Right Square Brace found before left one\n");
        }
        if (is_left_sq(* matrix)){
            left_sq++;
        }
        if (is_right_sq(* matrix)){
            right_sq++;
        }
        if (!is_digit(* matrix) && !is_left_sq(* matrix) && !is_right_sq(* matrix) && * matrix != ' ' && * matrix != ';'){
            error = 1;
            printf("Invalid Matrix: Found Unsupported Characters in Matrix.\n");
        }
    }
    return error;
}

/**************************************/
int parse_matrix(char * matrix)
{   double * arr_ptr = matrix_arr;
    int column_check_count = 0;
    char * ori_num_ptr, * num_ptr = malloc(10*sizeof(char));
    ori_num_ptr = num_ptr;
    if (is_left_sq(* matrix)){
        matrix++;
        while (!is_right_sq(* matrix)){
                if (is_digit(* matrix)){
                    memset(num_ptr, 0, sizeof(char)*10);
                    num_ptr = ori_num_ptr;
                    while (is_digit(* matrix)){
                        * num_ptr = * matrix;
                        if(is_digit(*(matrix+1))){
                            num_ptr++;
                            matrix++;
                        }
                        else break;
                    }
                    *(num_ptr+1)='\0';
                    * arr_ptr = atof(ori_num_ptr);
                    printf("array - %lf\n", *arr_ptr);
                    arr_ptr++;
                    if (rows == 1){
                        columns++;
                    }
                    column_check_count++;
                }
                else if (* matrix == ' '){
                    ;
                }
                else if (* matrix == ';'){
                    rows++;
                    if (rows > 1){
                        if (column_check_count == columns){
                            column_check_count = 0;
                        }
                        else{
                            printf("Invlaid Matrix: Columns are not same across rows.\n");
                            return 0;
                        }
                    }
                }
                matrix++;
        }
    
    }
    return 1;
} 

void main ()
{
    char * matrix_str;
    double sum;
    char nl;
    matrix_arr = malloc(256*sizeof(double));
    matrix_str = malloc(256*sizeof(char));
    while (1){
        rows = 1; 
        columns = 0;
        printf("\n\nThe input format for matrix is [a b c; d e f; g h i].\nPlease give space between two numbers.\nRows are Separated by semicolons and columns by spaces.\n");
        printf(">>\n");
        printf("Enter Required Matrix:\n");
        fgets(matrix_str, 256, stdin);
        printf("Enter the sum value to serach nxn matrix:\n");
        int sum_check = scanf("%lf%c", &sum, &nl);
        if (nl != '\n') continue;
        printf("Enter the value for n in nxn matrix:\n");
        nl = ' ';
        int n_check = scanf("%d%c", &size, &nl);
        if (nl != '\n') continue;
        int error = validate_matrix(matrix_str);
        if (!error){
            int check = parse_matrix(matrix_str);
            if (check){
                printf("Entered Matrix is having %d Rows and %d Columns\n", rows, columns);
                // fflush(stdout);
                /******************************************************/
                matrix = malloc(rows*sizeof(double *));
                for (int i = 0; i < rows; i++){
                    matrix[i] = malloc(columns*sizeof(double));
                }
                matrix_search(sum);
            }
            else{
                printf("Error in Matrix Input. Try Again.\n");
            }
        }
        else{
            printf("Error in Matrix Input. Try Again.\n");
        }
        break;
    }
    
}
