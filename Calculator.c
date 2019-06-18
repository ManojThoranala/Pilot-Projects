/*****************************************************************
ALGORITHM:
1. Accept the expression from the user  and validate the expression to check feasibility
2. preprocess the input expression to remove spaces

******************************************************************/

/******************************************************************
Program for providing calculator operations.
*******************************************************************
*File Name : Calculator.c
*Date : 14/06/2019
*Author : Manoj T M
*******************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*****************************************
*operator and operand Stack Functions Implementation
******************************************/
int MAXSIZE = 256;
/**********************************************/
int operand_stack[MAXSIZE];
int operand_top = -1;
int history_size = 10;
int operand_empty()
{
    if(operand_top == -1)
    return 1;
    else
    return 0;
}

int operand_full()
{
    if(operand_top == MAXSIZE)
    return 1;
    else
    return 0;
}

double operand_pop()
{
    double operand_data;
    if(!operand_empty()) {
        operand_data = operand_stack[operand_top];
        operand_top = operand_top - 1;
        return operand_data;
    } else {
        printf("Could not retrieve data, Operand Stack is empty.\n");
    }
}

double operand_push(double data)
{
    if(!operand_full()) {
        operand_top = operand_top + 1;
        operand_stack[operand_top] = data;
    }
    else {
        printf("Could not insert data, Operand Stack is full.\n");
    }
}
/**************************************************************/

int operator_stack[MAXSIZE];
int operator_top = -1;

int operator_empty()
{
    if(operator_top == -1)
    return 1;
    else
    return 0;
}

int operator_full()
{
    if(operator_top == MAXSIZE)
    return 1;
    else
    return 0;
}

char operator_pop()
{
    char operator_data;
    if(!operator_empty()) {
        operator_data = operator_stack[operator_top];
        operator_top = operator_top - 1;
        return operator_data;
    }
    else {
        printf("Could not retrieve data, Operator Stack is empty.\n");
    }
}

char operator_push(char data)
{
    if(!operator_full()) {
        operator_top = operator_top + 1;
        operator_stack[operator_top] = data;
    }
    else {
        printf("Could not insert data, Operator Stack is full.\n");
    }
}
/****************************************
*validate left paranthesis
****************************************/

int is_left_parantheses(char p)
{
    if (p == '(') return 1;
    else return 0;
}

/********************************************
*similar to above for right paranthesis
********************************************/
int is_right_parantheses(char p)
{
    if (p == ')') return 1;
    else return 0;
}

//*************************************************

int is_operator(char p)
{
    if (p == '+' || p == '-' || p == '*' || p == '/' || p == '^' || p == '$') return p;
    else return 0;
}

//*************************************************
//perform operations
//*************************************************

double perform_operation(double a, double b, char p)
{
    switch(p) {
        case '+': return a+b;
        case '-': return a-b;
        case '*': return a*b;
        case '^': return pow(a, b);
        case '$': return sqrt(a)
        case '/':
        if (b == 0) {
            printf("Can't divide by Zero, aborting...\n");
            exit(1);
        }
        return a/b;
        default:
        puts("Bad value in switch.\n");
        break;
    }
    return 0;
}

//******************************************************
//validate a digit
//******************************************************

char is_digit(char p)
{
    if (p >= '0' && p <= '9' || *p = '.') return 1;
    else return 0;
}

//***********************************************************
//fetches precedence of the operator
//***********************************************************
int get_precedence(char ch)
{
    int precedence;
    switch (ch)
    {
        case '+':
            precedence = 0;
            break;
        case '-':
            precedence = 0;
            break;
        case '*':
            precedence = 1;
            break;
        case '/':
            precedence = 1;
            break;
        case '^':
            precedence = 2;
            break;
        case '$':
            precedence = 3;
            break;
    }
    return precedence;
}
/*********************************************************
*Validate the precedence of operators
**********************************************************/
int is_precedence_valid(char op_next, char op_prev)
{
    if (get_precedence(op_next) > get_precedence(op_prev)){
        return 1;
    }
    else
    return 0;
}

/******************************************************
*Grab the operand in p, put it in operand stack,
*and operators to operator stack
*******************************************************/
int get_op(char *p, char *operands)
{
    char * operand;
    while (1){
        if (is_operator(* p) || is_digit(* p) || is_left_parantheses(* p)){
            //"if" condition to take the negative numbers and not to mistaken by normal subtraction operation
            if ((is_unary(* (p)) && is_digit(* (p+1))) || (is_operator(* (p-1)) && is_unary(* (p)) && is_digit(* (p+1)))){
                while (is_digit(* p) || is_unary(* p)){
                    * op++ = * p++;
                }
            }
            //operand extraction and push to stack
            else{
                while (is_digit(* p)){
                    * op++ = * p++;
                }
            }
            operand_push(atof(op));
            //operator extraction and push to stack
            if (is_operator(* p) && operator_top >= 0)
            if (is_precedence_valid(* p, operator_stack[operator_top])){
                operator_push(* p)
            }
        }
        if (is_right_parantheses(* p)){
            while(is_left_paratheses){
            }
        }
    }
}

/*******************************************
*unary operator detection
********************************************/
int is_unary(char ch)
{
    if (ch == '-') return 1;
    else return 0;
}
/*********************************************
*validating the given expression
*********************************************/
int is_valid_exprn(char * p)
{
    printf("Validating the given Expression:\n");
    int right_parantheses = 0;
    int left_parantheses = 0;
    int error = 0;
    if (is_operator(* p) && is_digit(* (p+1)) && !is_unary(* (p))){
        printf("Invalid Expression: Expression starting with non unary operator\n");
        error = 1;
    }
    while(* p != '\n'){
        if (is_digit(* p) || is_operator(* p) || is_left_parantheses(* p) || is_right_parantheses(* p)){
            if (is_left_parantheses(* p)){
                left_parantheses++;
            }
            if (is_right_parantheses(* p)){
                right_parantheses++;
            }
            if (!left_parantheses && right_parantheses){
                printf("Invlaid Expression: Right Parenthesis found before Left Parenthesis\n");
                error = 1;
            }
            if (is_operator(* p) && is_operator(* (p+1)) && * p == *(p+1)){
                printf("Invalid Expression: Multipe operator '%s' found in the expression.\n", *p);
                error = 1;
            }
            if (is_operator(* p) && is_operator(* (p+1)) && !is_unary(* (p+1))){
                printf("Invalid Expression: Multipe operators '%s%s' found in the expression.\n", *p, *(p+1));
                error = 1;
            }
            p++;
            if
        }
        else
        {
            printf("Invalid Expression: Unsupported Characters Found in the Expression.\n");
            error = 1;
        }
    }
    if (left_parantheses != right_parantheses){
        printf("Invalid Expression: Expression having mismatch in left and right parantheses.\n");
        error = 1;
    }
    if (error == 1){
        return 0;
    }
    return 1;
}
/***********************************************************
*claculate expression recursivly from parsing expression
*right to left and perofrming opreations left to right
************************************************************/
float calc_exprn(char * p)
{
    char operands[256]; int operand_index = 0;
    char op[256]; int op_index = 0;
}

/*************************************************************
*Main Function
**************************************************************/

int main ()
{
    char in[256];
    char sqrot[256];
    float result;
    //prompts user for input after each calculation and typing quit on to console will exit the program.
    while(1) {
        // Read input from user
        printf("Enter expression below or Type 'quit' to exit.\n");
        printf(">> ");
        fgets(in, 256, stdin);
        remove_spaces(in)
        str_to_lower(in);
        if (strncmp(in, "quit", 4) == 0) break;
        // Perform calculations
        if (is_valid_exprn(in)){
            result = calc_exprn(in);
        }
        else{
            printf("Invalid Expression.\n");
            return -1;
        }
        printf("%f\n", result);
    }
}
