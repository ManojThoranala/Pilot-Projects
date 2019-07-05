/******************************************************************
 * Program to compress and encode the text present in the file.
 ******************************************************************/

/******************************************************************
 * ALGORITHM:
 *          1. Accepts input from the user for the csv file name
 *          2. Obtain the file steam pointer to the csv file
 *          3. Ask the user for the operation to perform add, search, show all details
 *                a.To add the employee details call function add details
 *                b.Function called in step 3.a prompts user to give all the details about the employee
 *                     and program will generate unique id and assigns to employee
 *          4. To search employee get details function is called
 *              a. Fucntion called in step 4 prompts user to input for the search by particular of the employee
 *              b. displays the mathched rows from the file
 *          5. To Showall details the file is iterated and all the rows are displayed.
 * Parsing the CSV file:
 *              1. The CSV file here considered is with delimiter ";"
 *              2. The function get field is used to get the particular details of the employee in the rows in a file.
 *              3. strtok is used to extract the string followed by ; delimiter 
 *******************************************************************/

/*******************************************************************
*File Name : assignment_1_1.c
*Date : 04/07/2019
*Author : Manoj T M
*Org : PathPartner Technology
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define MAX_FILE_NAME_LEN 512
#define MAX_NAME_LEN 256
#define MAX_MAIL_LEN 256
#define MAX_DOB_LEN 16
#define MAX_TEAM_NAME_LEN 256
#define MAX_ID_LEN 256

/******************************************
 * Structure to hold the employee details 
 * unitl they are written to file 
******************************************/
typedef struct emp_data{
char name[MAX_NAME_LEN];
char mail[MAX_MAIL_LEN];
char dob[MAX_DOB_LEN];
char team[MAX_TEAM_NAME_LEN];
int emp_id;
} employee_db;

/******************************************
 * Function to capture the particular data like name, mailid of the employee
 * returns a cont char pointer to callee
 *****************************************/
const char* getfield(char * line, int num)
{
    char * temp = strdup(line);
    const char * tok;
    for (tok = strtok(temp, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

/***************************************************
 * Function to generate the unique id for each employee added to file
 ***************************************************/
int get_emp_id(employee_db * emp_db, FILE * fh){
    int max_id = 0;
    char line[MAX_FILE_NAME_LEN] = {0};
    for (int i = 0; (fgets(line, sizeof(char)*MAX_FILE_NAME_LEN, fh)) != NULL; i++){
        if (i==0){
            ;
        }
        else{
                char * temp = line;
                int temp_id = atoi(getfield(temp, 5));
                if (max_id < temp_id){
                    max_id = temp_id;
                }
        }
    }
    emp_db->emp_id = max_id + 1;
    return 0;
}

/***********************************************
 * Function to remove the new line character in the 
 * data, as implementation is using fgets this is necessary
 ************************************************/
int remove_nl(char * string){
    char *pos;
    if ((pos=strchr(string, '\n')) != NULL)
        *pos = '\0';
    else
        {
            printf("String is too long\n");
        }
    return 0;
}

/**********************************************
 * Function ot print the employee details in the file
 **********************************************/
int printline(int row_no, char * line){
    char * temp = line;
    printf("Row: %d; Name: %s; E-Mail: %s; DOB: %s; Team: %s; ID: %s;\n", row_no, getfield(temp, 1), getfield(temp, 2), getfield(temp, 3), getfield(temp, 4), getfield(temp, 5));
    return 0;
}

/****************************************************
 * Function to add the employee details
 ****************************************************/

int add_details (FILE * fh){
    employee_db emp_db;
    printf("\t\t\tINSERT EMPLOYEE DETAILS\n\n");
    printf("------------------------------------------------------------\n");
    printf("1.\tEnter the Name of the Employee:\n");
    fflush(NULL);
    fgets(emp_db.name, sizeof(char)*MAX_NAME_LEN, stdin);
    remove_nl(emp_db.name);
    printf("2.\tEnter the E-mail ID of the Employee:\n");
    fflush(NULL);
    fgets(emp_db.mail, sizeof(char)*MAX_MAIL_LEN, stdin);
    remove_nl(emp_db.mail);
    printf("3.\t Enter the Date of Brith of the Employee(Date Format - DD/MM/YYYY):\n");
    fflush(NULL);
    fgets(emp_db.dob, sizeof(char)*MAX_DOB_LEN, stdin);
    remove_nl(emp_db.dob);
    printf("4.\tEnter the Team Name of the Employee:\n");
    fflush(NULL);
    fgets(emp_db.team, sizeof(char)*MAX_TEAM_NAME_LEN, stdin);
    remove_nl(emp_db.team);
/* Since the employee id are unique. Program generates the ID and updates the file*/
    get_emp_id(&emp_db, fh);
    printf("5. The Employee ID (Program Generated) for the Employee %s is: %d\n", emp_db.name, emp_db.emp_id);
/* fprintf to add the row in the file */
    fprintf(fh, "%s;%s;%s;%s;%d;\n", emp_db.name, emp_db.mail, emp_db.dob, emp_db.team, emp_db.emp_id);
    printf("Employee %s Details Added Successfully...\n", emp_db.name);
    return 0;
}

/****************************************************
 * Function to fetch the details of the employee
 *******************************************************/

int get_details (FILE * fh){
    char search_str[MAX_NAME_LEN]; /* variable to hold Search string */
    printf("\t\t\tSEARCH EMPLOYEE DETAILS\n\n");
    printf("------------------------------------------------------------\n");
    printf("Enter the particular of the Employee to search:\n");
    fflush(stdin);
    fgets(search_str, sizeof(char)*MAX_NAME_LEN, stdin);
    char line[MAX_FILE_NAME_LEN]= {0};
    int flag = 0;
    for (int i = 0; (fgets(line, sizeof(char)*MAX_FILE_NAME_LEN, fh)) != NULL; i++){
        if (i==0){
            ;
        }
        else{
            char * temp = line;
            int len = strlen(search_str) - 1;
/* displaying the employee details if the string matches with any field in a row of the file */
            if (strncmp(getfield(temp, 1), search_str, len) == 0){
                printline(i, line);
                flag = 1;
            }
            else if (strncmp(getfield(temp, 2), search_str, len) == 0){
                printline(i, line);
                flag = 1;
            }
            else if (strncmp(getfield(temp, 3), search_str, len) == 0){
                printline(i, line);
                flag = 1;
            }
            else if (strncmp(getfield(temp, 4), search_str, len) == 0){
                printline(i, line);
                flag = 1;
            }
            else if (atoi(search_str) == atoi(getfield(temp, 5))){
                printline(i, line);
                flag = 1;
            }
        }
    }
    if (flag == 0){
        printf("No Matching Details found with %s\n.", search_str);
    }
    return 0;
}

/******************************
 * Main Function
 *****************************/
int main (){
    FILE * fh_rw;
    char * file_name;
    file_name = "EmployeeDetails.csv";
    char * temp, * choice;
    temp = malloc(sizeof(char)*3);
    choice = malloc(sizeof(char)*3);
    /* Giving the user an option to give the cvs file if he wants */
    printf("CSV file selected is %s. \nIf need to change the file. Enter y/n.\n", file_name);
    fgets(temp, sizeof(char)*3, stdin);
    if ((strncmp(temp, "y", 1) == 0) || (strncmp(temp, "Y", 1) == 0)){
        printf("Enter the CSV file name or path:\n");
        file_name = NULL;
        file_name = malloc(sizeof(char) * MAX_FILE_NAME_LEN);
        fgets(file_name, sizeof(char) * MAX_FILE_NAME_LEN, stdin);
        remove_nl(file_name);
    }
    else if ((strncmp(temp, "n", 1) == 0) || (strncmp(temp, "N", 1) == 0)){
        ;
    }
    /* Future Scope - To add the logic to test if given file is a csv or not. */

    if(access( file_name, F_OK ) != -1){
        if ((fh_rw = fopen(file_name, "r+")) != NULL){
        }
        else{
            printf("Bad File Open in read plus mode:%s\n", strerror(errno));
        }
    } 
    else {
        printf("%s is not found. Creating the file.\n", file_name);
        if ((fh_rw = fopen(file_name, "w+")) != NULL){
            fprintf(fh_rw, "NAME; E_MAIL; DOB; TEAM; EMPLOYEE_ID;\n");
        }
        else{
            printf("Bad File Open in write plus mode:%s\n", strerror(errno));
        }
    }         
    int file_open_flag = 1;
    while(1){
            printf("\nFile selected for operation is : %s\n", file_name);
        if ((fh_rw = fopen(file_name, "r+")) == NULL && !file_open_flag){
                printf("Bad File Open in write plus mode:%s\n", strerror(errno));
            }
        file_open_flag = 0;
        memset(choice, '0', sizeof(char));
        printf("------------------------------------------------------------\n");
        printf("Select the choices below:\n1 - Add the Employee Details\n2 - Search the Employee Details by - Name / E-mail / DOB / Team / Employee-ID\n3 - Show the all Employees data\n");
        fflush(NULL);
        fgets(choice, sizeof(char)*3, stdin);
        if (strncmp(choice, "1", 1) == 0){
            add_details(fh_rw);
            fflush(NULL);
        }
        else if (strncmp(choice, "2", 1) == 0){
            get_details(fh_rw);
            fflush(NULL);
        }
        else if(strncmp(choice, "3", 1) == 0){
            fflush(NULL);
            printf("\t\t\tALL EMPLOYEE DETAILS\n\n");
            printf("------------------------------------------------------------\n");
            char line[MAX_FILE_NAME_LEN] = {0};
            for (int i = 0; (fgets(line, sizeof(char)*MAX_FILE_NAME_LEN, fh_rw)) != NULL; i++){
                if(i == 0){
                    ;
                }
                else{
                    printline(i, line);
                }
            }
        }
        else{
            printf("Worng choice. Try Again.\n");
        }
    fclose(fh_rw);
    }
    return 0;
}
