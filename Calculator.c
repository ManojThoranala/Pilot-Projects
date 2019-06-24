/*****************************************************************
ALGORITHM:
	1. Accept the expression from the user and validate the expression to check feasibility
	2. The expression is sent to calculate expression function where the operators and operands are extracted 
	   and stored in user created stacks (arrays)- stacks are implemented with push and pop functions
	3. The function in step2 calls function to perform operation according to the precedence of operators
	4. The result at the end is printed.

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
double operand_stack[256];
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
*Data structure to stotre the 
history of calculator operations
*****************************************/
typedef struct node
{
    char exprn[256];
    double result;
    struct node *next;
    struct node *prev;
} history_node;
history_node *head = NULL;
int hist_count = 0;
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
    case '-':
        precedence = 0;
        break;
    case '*':
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
int is_unary(char *ch)
{
    if (*ch == '-' && (is_digit(*(ch + 1)) || is_left_parantheses(*(ch + 1))))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*******************************************
*sqrt operator detection
********************************************/
int is_sqrt(char *ch)
{
    if (*ch == '$' && (is_digit(*(ch + 1)) || is_operator(*(ch - 1)) || is_left_parantheses(*(ch + 1))))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/******************************************************
*Grab the operand in p, put it in operand stack,
*and operators to operator stack
*******************************************************/
int calc_exprn(char *p)
{
    printf("Calculating the Expression ...\n");
    char *op;
    op = malloc(100 * sizeof(char));
    char *op_ptr = op;
    int dot_count = 0;
    while (*p != '\n')
    {
        if (is_operator(*p) || is_digit(*p) || is_left_parantheses(*p) || is_right_parantheses(*p))
        {
            //"if" condition to take the negative numbers and not to mistaken by normal subtraction operation

            if (is_digit(*p) || (is_unary(p) && operand_top == -1) || (is_operator(*(p - 1)) && is_unary(p)))
            {
                memset(op, 0, sizeof(char) * 100);
                op = op_ptr;
                dot_count = 0;
                while (is_digit(*p) || is_unary(p))
                {
                    *op = *p;
                    if (*p == '.')
                    {
                        if (dot_count > 1)
                        {
                            break;
                        }
                        else
                            dot_count++;
                    }
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
                        double operand2 = operand_pop();
                        double operand1;
                        if (operator== '$')
                        {
                            operand1 = 0.0;
                            if (!op_error || !opnd_error)
                            {
                                double res = perform_operation(operator, operand2, operand1);
                                operand_push(res);
                                if (!is_precedence_valid(*p, operator_stack[operator_top]))
                                    continue;
                                operator_push(*p);
                            }
                            else
                            {
                                printf("Stack Error.\n");
                                calc_err = 1;
                                return 0;
                            }
                        }
                        else
                        {
                            operand1 = operand_pop();
                            if (!op_error || !opnd_error)
                            {
                                double res = perform_operation(operator, operand1, operand2);
                                operand_push(res);
                                if (!is_precedence_valid(*p, operator_stack[operator_top]))
                                    continue;
                                operator_push(*p);
                            }
                            else
                            {
                                printf("Stack Error.\n");
                                calc_err = 1;
                                return 0;
                            }
                        }
                    }
                }
                else
                {
                    operator_push(*p);
                }
            }
            else if (is_left_parantheses(*p))
            {
                operator_push(*p);
            }
            else if (is_right_parantheses(*p))
            {
                while (1)
                {
                    double operand2, operand1;
                    char operator= operator_pop();
                    if (is_left_parantheses(operator))
                        break;
                    operand2 = operand_pop();
                    if (operator== '$')
                    {
                        operand1 = 0.0;
                        if (!op_error || !opnd_error)
                        {
                            double res = perform_operation(operator, operand2, operand1);
                            operand_push(res);
                        }
                        else
                        {
                            printf("Stack Error.\n");
                            calc_err = 1;
                            return 0;
                        }
                    }
                    else
                    {
                        operand1 = operand_pop();
                        if (!op_error || !opnd_error)
                        {
                            double res = perform_operation(operator, operand1, operand2);
                            operand_push(res);
                        }
                        else
                        {
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
        if (operator== '$')
        {
            operand1 = 0.0;
            if (!op_error || !opnd_error)
            {
                double res = perform_operation(operator, operand2, operand1);
                operand_push(res);
            }
            else
            {
                printf("Stack Error.\n");
                calc_err = 1;
                return 0;
            }
        }
        else
        {
            operand1 = operand_pop();
            if (!op_error || !opnd_error)
            {
                double res = perform_operation(operator, operand1, operand2);
                operand_push(res);
            }
            else
            {
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
    printf("Validating the given Expression ...\n");
    int right_parantheses = 0;
    int left_parantheses = 0;
    int error = 0;
    if (is_operator(*p) && !is_unary(p) && !is_sqrt(p))
    {
        printf("Invalid Expression: Expression starting with non unary operator\n");
        error = 1;
    }
    while (*p != '\n')
    {
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
            if (is_operator(*p) && is_operator(*(p + 1)) && *p == *(p + 1) && !is_sqrt(p))
            {
                printf("Invalid Expression: Multiple operator '%s' found in the expression.\n", p);
                error = 1;
            }
            if (is_operator(*p) && is_operator(*(p + 1)) && !is_unary(p + 1) && !is_sqrt(p + 1))
            {
                printf("Invalid Expression: Multiple operators '%s%s' found in the expression.\n", p, (p + 1));
                error = 1;
            }
        }
        else if (*p == ' ')
        {
            ;
        }
        else
        {
            printf("Invalid Expression: Unsupported Characters Found in the Expression.\n");
            error = 1;
        }
        p++;
    }
    if (left_parantheses != right_parantheses)
    {
        printf("Invalid Expression: Expression having mismatch in left and right parantheses.\n");
        error = 1;
    }
    if (error == 1)
    {
        return 0;
    }
    return 1;
}

/*********************************************************
 * Insert the histrory node into list
 *********************************************************/
int append_history(char *exp, double res)
{
    history_node **start = &head;

    if (*start == NULL)
    {
        history_node *new_hist_node = malloc(sizeof(history_node));
        int i = 0;
        while (*exp != '\n')
        {
            new_hist_node->exprn[i] = *exp;
            exp++;
            i++;
        }
        new_hist_node->exprn[i + 1] = '\0';
        new_hist_node->result = res;
        new_hist_node->next = new_hist_node;
        new_hist_node->prev = new_hist_node->next;
        *start = new_hist_node;
    }
    else if (hist_count != history_size)
    {
        history_node *last_node = (*start)->prev;
        history_node *new_hist_node = malloc(sizeof(history_node));
        int i = 0;
        while (*exp != '\n')
        {
            new_hist_node->exprn[i] = *exp;
            exp++;
            i++;
        }
        new_hist_node->exprn[i + 1] = '\0';
        new_hist_node->result = res;
        new_hist_node->next = *start;
        (*start)->prev = new_hist_node;
        new_hist_node->prev = last_node;
        last_node->next = new_hist_node;
        if (hist_count == history_size)
        {
            new_hist_node->next = head;
            head->prev = new_hist_node;
        }
    }
    else if (hist_count == history_size)
    {
        int i = 0;
        while (*exp != '\n')
        {
            head->exprn[i] = *exp;
            exp++;
            i++;
        }
        head->exprn[i + 1] = '\0';
        head->result = res;
        head = head->next;
    }
}

/***********************************************************
 * Display the history contents
 ***********************************************************/
int display_list()
{
    history_node *temp = head;
    puts("\t\t\tHISTORY");
    while (temp->next != head)
    {
        printf("%s = %.3lf\n", temp->exprn, temp->result);
        temp = temp->next;
    }
    printf("%s = %.3lf\n", temp->exprn, temp->result);
}
/*************************************************************
*Main Function
**************************************************************/

int main()
{
    char in[256];
    double result = 0.0;
    //prompts user for input after each calculation and typing quit on to console will exit the program.
    while (1)
    {
        op_error = 0;
        opnd_error = 0;
        calc_err = 0;
        result = 0.0;

        // Read input from user
        puts("Supported operators +, -, *, / - General, ^ - Power, $ - Square Root. For square root of 'a' use $a.");
        puts("Type 'hist' to get the recent 10 operations. Type 'quit' to exit.");
        printf("\nEnter expression below:\n");
        printf(">> ");
        if (!fgets(in, 256, stdin))
        {
            break;
        }
        if (strncmp(in, "quit", 4) == 0)
            break;
        if (strncmp(in, "hist", 4) == 0)
        {
            printf("Below are the recent %d operations performed,\n\n", history_size);
            if (head != NULL)
            {
                display_list();
            }
            else
            {
                printf("History is empty!\n\n");
            }
            continue;
        }
        // Perform calculations
        if (is_valid_exprn(in))
        {
            int success = calc_exprn(in);
            if (calc_err && !success)
            {
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
        printf("Result of the Expression %s = \n", in);
        printf("%.3lf\n\n\n", result);
        append_history(in, result);
        if(hist_count != history_size) hist_count++;
    }
}
