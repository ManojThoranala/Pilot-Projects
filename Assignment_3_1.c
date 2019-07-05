/******************************************************************
 * Program to compress and encode the text present in the file.
 ******************************************************************/

/******************************************************************
 * ALGORITHM:
 *          1. Accept the file name to processed from the user.
 *          2. Validate the file format and open the file in read and write mode
 *          3. open two file streams pointing to the input file as read and another as write plus - temp file
 *          4. Now get the character from the input file and count the number of consequent occurances of the character
 *          5. Once the new character is seen write the old character and its numbers occurances to temp file
 *          6. When input file reaches EOF write the last remaining character to temp file and close the file streams
 *          7. Now open two more file streams to read from temop file and write to input file.
 *          8. Until the EOF is reached write all the character to input file and close the file streams and remove the temp file.
 *          9. And exit.
 ******************************************************************/

/*******************************************************************
*File Name : assignment_1_1.c
*Date : 02/07/2019
*Author : Manoj T M
*Org : PathPartner Technology
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_FILE_NAME_LEN 1000 /* Max File Name length */
#define MAX_NUM_LEN 256 /* Max occurance Number length */


int file_compress_encode(const char *file_path)
{
    FILE *fh_read, *fh_write; /* File streams to read and write */
    int c = 0;                /* variable to store the read character and track the previous character*/
    int prev_c = 0;
    int count_c = 1;           /* Character Occurance count */
    char  * temp;               /* variable to store the Occurance count in string format */
    FILE * read_at, * write_at; /* file streams for copying back the encoded and compressed from temp file to input file */
    temp = malloc(sizeof(char) * MAX_NUM_LEN);
    if (temp == NULL){
        printf("Bad Malloc:%s\n", strerror(errno));
    }
    if ((fh_read = fopen(file_path, "r")) == NULL)
    {
        printf("File Error: Couldnot open the file in read mode:\n%s\n", strerror(errno));
        return 0;
    }
    if ((fh_write = fopen("temp", "w+")) == NULL)
    {
        printf("File Error: Couldnot open the file in write plus mode:\n%s\n", strerror(errno));
        return 0;
    }
    c = fgetc(fh_read);
    prev_c = c;
    if (c != NULL || c != '\0'){
        ungetc(c, fh_read);
    }
    while ((c = fgetc(fh_read)) != EOF)
    {
        /* Remove the first if condition and block inside it, to compress and encode the newline character also */
        if (c == '\n'){
            fputc(prev_c, fh_write);
            if (count_c > 1){
                sprintf(temp, "%d", count_c);
                for(int i = 0; temp[i] != '\0'; i++){
                    fputc(temp[i], fh_write);
                }
            }
            count_c = 1;
            prev_c = c;
        }
        else if (c != prev_c)
        {
            fputc(prev_c, fh_write);
            if (count_c > 1)
            {
                /* Uncomment the below lines to get curly braces around the number of occurances of a alphabet*/
                //fputc((int)'{', fh_write);
                sprintf(temp, "%d", count_c);
                for(int i = 0; temp[i] != '\0'; i++){
                    fputc(temp[i], fh_write);
                }
                //fputc((int)'}', fh_write);
            }
            count_c = 1;
            prev_c = c;
        }
        else if (c == prev_c)
        {
            count_c++;
        }
        
    }
    if (c != prev_c)
        {
            fputc(prev_c, fh_write);
            if (count_c > 1)
            {
                /* Uncomment the below lines to get curly braces around the number of occurances of a alphabet*/
                //fputc((int)'{', fh_write);
                sprintf(temp, "%d", count_c);
                for(int i = 0; temp[i] != '\0'; i++){
                    fputc(temp[i], fh_write);
                }
                //fputc((int)'}', fh_write);
            }
            count_c = 1;
            prev_c = c;
        }
        else if (c == prev_c)
        {
            count_c++;
        }
    fputc(c, fh_read);
    if (feof(fh_read))
    {
        printf("End of File Reached.\n");
        fgetc(fh_read);
    }
    else
    {
        printf("Error Occured: %s\n", strerror(errno));
        fgetc(fh_read);
        return 0;
    }
    fclose(fh_read);
    fclose(fh_write);
    if ((read_at = fopen("temp", "r")) == NULL)
    {
        printf("File Error: Couldnot open the file in read mode:\n%s\n", strerror(errno));
        return 0;
    }
    if ((write_at = fopen(file_path, "w")) == NULL)
    {
        printf("File Error: Couldnot open the file in write plus mode:\n%s\n", strerror(errno));
        return 0;
    }
    c = 0;
    while((c = fgetc(read_at)) != EOF){
        fputc(c, write_at);
    }
    fputc(c, read_at);
    if (feof(read_at))
    {
        fgetc(read_at);
        fgetc(write_at);
    }
    else
    {
        printf("Error Occured: %s\n", strerror(errno));
        fgetc(read_at);
        fgetc(write_at);
        return 0;
    }
    fclose(read_at);
    fclose(write_at);
    if(remove("temp") != 0){
        printf("Bad File Remove: %s\n", strerror(errno));
    }
    free(temp);
}

int main()
{
    char *file;
    file = malloc(sizeof(char) * MAX_FILE_NAME_LEN);
    printf("Enter the path for the input file:\n");
    scanf("%s", file);
    int check = file_compress_encode(file);
    if (!check){
        return -1;
    }
    return 0;
}