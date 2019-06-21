/*****************************************************************
ALGORITHM:
1. Accept the expression from the user  and validate the expression to check feasibility
2. preprocess the input expression to remove spaces

******************************************************************/

/******************************************************************
Program for providing calculator operations.
*******************************************************************
*File Name : assignment_1_3.c
*Date : 14/06/2019
*Author : Manoj T M
*Org : PathPartner Technology
*******************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*****************************************
*operator and operand Stack Functions Implementation
******************************************/
int MAXSIZE = 256;
int operator_stack[256];
int operator_top = -1;
int operand_stack[256];
int operand_top = -1;
int history_size = 10;
int op_error = 0;
int opnd_error = 0;
int calc_err = 0;
/**********************************************/

int operand_empty()
{
    if (operand_top == -1)
        return 1;
    else
        return 0;
}

int operand_full()
{
    if (operand_top == MAXSIZE)
        return 1;
    else
        return 0;
}

double operand_pop()
{
    double operand_data;
    if (!operand_empty())
    {
        operand_data = operand_stack[operand_top];
        operand_top = operand_top - 1;
        return operand_data;
    }
    else
    {
        printf("Could not retrieve data, Operand Stack is empty.\n");
        opnd_error = 1;
        return 1.0;
    }
}

double operand_push(double data)
{
    if (!operand_full())
    {
        operand_top = operand_top + 1;
        operand_stack[operand_top] = data;
    }
    else
    {
        printf("Could not insert data, Operand Stack is full.\n");
        return 0.0;
    }
}
/**************************************************************/

int operator_empty()
{
    if (operator_top == -1)
        return 1;
    else
        return 0;
}

int operator_full()
{
    if (operator_top == MAXSIZE)
        return 1;
    else
        return 0;
}

char operator_pop()
{
    char operator_data;
    if (!operator_empty())
    {
        operator_data = operator_stack[operator_top];
        operator_top = operator_top - 1;
        return operator_data;
    }
    else
    {
        printf("Could not retrieve data, Operator Stack is empty.\n");
        op_error = 1;
        return 1.0;
    }
}

char operator_push(char data)
{
    if (!operator_full())
    {
        operator_top = operator_top + 1;
        operator_stack[operator_top] = data;
    }
    else
    {
        printf("Could not insert data, Operator Stack is full.\n");
        return 0.0;
    }
}
/****************************************
*validate left paranthesis
****************************************/

int is_left_parantheses(char p)
{
    if (p == '(')
        return 1;
    else
        return 0;
}

/********************************************
*similar to above for right paranthesis
********************************************/
int is_right_parantheses(char p)
{
    if (p == ')')
        return 1;
    else
        return 0;
}

//*************************************************

int is_operator(char p)
{
    if (p == '+' || p == '-' || p == '*' || p == '/' || p == '^' || p == '$')
        return p;
    else
        return 0;
}

//*************************************************
//perform operations
//*************************************************

double perform_operation(char op, double a, double b)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '^':
        return pow(a, b);
    case '$':
        return sqrt(a);
    case '/':
        if (b == 0)
        {
            printf("Can't divide by Zero, aborting...\n");
            exit(1);
        }
        return a / b;
    default:
        puts("Bad value while Performing operation\n");
        break;
    }
    return 0;
}

//******************************************************
//validate a digit
//******************************************************

int is_digit(char p)
{
    if (p >= '0' && p <= '9' || p == '.')
        return 1;
    else
        return 0;
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
    if (get_precedence(op_next) > get_precedence(op_prev))
    {
        return 1;
    }
    else
        return 0;
}

/*******************************************
*unary operator detection
********************************************/
int is_unary(char * ch)
{
    if (* ch == '-' && is_digit(* (ch + 1)))
        return 1;
    else
        return 0;
}

/******************************************************
*Grab the operand in p, put it in operand stack,
*and operators to operator stack
*******************************************************/
int calc_exprn(char *p)
{
    printf("Calculating the Expression:\n");
    char *op;
    op = malloc(100 * sizeof(char));
    char *op_ptr = op;
    while (*p != '\n')
    {
        if (is_operator(*p) || is_digit(*p) || is_left_parantheses(*p) || is_right_parantheses(*p))
        {
            //"if" condition to take the negative numbers and not to mistaken by normal subtraction operation
            if (is_digit(*p) || (is_unary(p) && operand_top == -1)|| (is_operator(*(p - 1)) && is_unary(p)))
            {
                memset(op, 0, sizeof(char) * 100);
                op = op_ptr;
                while (is_digit(*p) || is_unary(p))
                {   *op = *p;
                    if (is_digit(*(p + 1)))
                    {
                        op++;
                        p++;
                    }
                    else
                        break;
                }
                *(op + 1) = '\0';
                //after operand extraction push it to stack
                operand_push(atof(op_ptr));
            }
            
            //operator extraction and push to stack
            if (is_operator(*p))
            {
                if (operator_top >= 0)
                {
                    if (is_precedence_valid(*p, operator_stack[operator_top]))
                    {
                        operator_push(*p);

                    }
                    else
                    {
                        char operator= operator_pop();
                        double operand2 = operand_pop(), operand1;
                        if (operator == '$'){
                            operand1 = 0.0;
                            if (!op_error || !opnd_error){
                                double res = perform_operation(operator, operand2, operand1);
                                operand_push(res);
                                if (!is_precedence_valid(*p, operator_stack[operator_top])) continue;
                                operator_push(*p);

                            }
                            else{
                                printf("Stack Error.\n");
                                calc_err = 1;
                                return 0;
                            }
                        }
                        else
                        {   operand1 = operand_pop();
                            if (!op_error || !opnd_error){
                                double res = perform_operation(operator, operand1, operand2);
                                operand_push(res);
                                if (!is_precedence_valid(*p, operator_stack[operator_top])) continue;
                                operator_push(*p);
                            }
                            else{ 
                                printf("Stack Error.\n");
                                calc_err = 1;
                                return 0;
                            }
                        }
                    }
                }
                else{
                    operator_push(*p);
                }
            }
            else if (is_left_parantheses(* p)){
                operand_push(*p);
            }
            else if (is_right_parantheses(* p)){
                double operand2, operand1;
                operand2 = operand_pop();
                while (is_left_parantheses(operand2))
                {
                    char operator = operator_pop();
                    if (operator == '$'){
                        operand1 = 0.0;
                        if (!op_error || !opnd_error){
                            double res = perform_operation(operator, operand2, operand1);
                            operand_push(res);
                        }
                        else{
                            printf("Stack Error.\n");
                            calc_err = 1;
                            return 0;
                        }
                    }
                    else{
                        operand1 = operand_pop();
                        if (!op_error || !opnd_error){
                            double res = perform_operation(operator, operand1, operand2);
                            operand_push(res);
                        }
                        else{
                            printf("Stack Error.\n");
                            calc_err = 1;
                            return 0;
                        }
                    }
                }
            }
        }
        else if (*p == ' ')
        {
            ;
        }
        p++;
    }
    while (operator_top != -1)
    {
        double operand1;
        double operand2 = operand_pop();
        char operator= operator_pop();
        if (operator == '$'){
            operand1 = 0.0;
            if (!op_error || !opnd_error){
                double res = perform_operation(operator, operand2, operand1);
                operand_push(res);
            }
            else{
                printf("Stack Error.\n");
                calc_err = 1;
                return 0;
            }
        }
        else{
            operand1 = operand_pop();
            if (!op_error || !opnd_error)
            {
                double res = perform_operation(operator, operand1, operand2);
                operand_push(res);
            }
            else{
                printf("Stack Error.\n");
                calc_err = 1;
                return 0;
            }
        }
    }

    return 1;
}

/*********************************************
*validating the given expression
*********************************************/
int is_valid_exprn(char *p)
{
    printf("Validating the given Expression:\n");
    int right_parantheses = 0;
    int left_parantheses = 0;
    int error = 0;
    if (is_operator(*p) && !is_unary(p))
    {
        printf("Invalid Expression: Expression starting with non unary operator\n");
        error = 1;
    }
    while (*p != '\n'){
        if (is_digit(*p) || is_operator(*p) || is_left_parantheses(*p) || is_right_parantheses(*p))
        {
            if (is_left_parantheses(*p))
            {
                left_parantheses++;
            }
            if (is_right_parantheses(*p))
            {
                right_parantheses++;
            }
            if (!left_parantheses && right_parantheses)
            {
                printf("Invlaid Expression: Right Parenthesis found before Left Parenthesis\n");
                error = 1;
            }
            if (is_operator(*p) && is_operator(*(p + 1)) && *p == *(p + 1) && *p != '$')
            {
                printf("Invalid Expression: Multiple operator '%s' found in the expression.\n", p);
                error = 1;
            }
            if (is_operator(*p) && is_operator(*(p + 1)) && !is_unary(p + 1) && *(p + 1)!= '$')
            {
                printf("Invalid Expression: Multiple operators '%s%s' found in the expression.\n", p, (p + 1));
                error = 1;
            }
            p++;
        }
        else if (*p == ' '){
            p++;
            continue;
        }
        else{
            printf("Invalid Expression: Unsupported Characters Found in the Expression.\n");
            p++;
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

/*************************************************************
*Main Function
**************************************************************/

int main()
{
    char in[256];
    double result;
    //prompts user for input after each calculation and typing quit on to console will exit the program.
    while (1)
    {
        op_error = 0;
        opnd_error = 0;
        calc_err = 0;
        // Read input from user
        printf("Enter expression below or Type 'quit' to exit.\n");
        printf(">> ");
        fgets(in, 256, stdin);
        if (strncmp(in, "quit", 4) == 0)
            break;
        if (strncmp(in, "hist", 4) == 0){
            printf("Below are the recent %d operations performed", history_size);

        }
        // Perform calculations
        if (is_valid_exprn(in))
        {
            result = calc_exprn(in);
            if (calc_err){
                printf("Error in Calculation\n");
                continue;
            }
        }
        else
        {
            printf("Invalid Expression.\n\n\nTry Again.");
            continue;
        }
        result = operand_pop();
        printf("Result of the Expression is - \n");
        printf("%.3lf\n", result);
    }
}
