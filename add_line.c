//AARON HABANA
//COMP 322
//GABROVSKY

/*
*   WRITE A PROGRAM WHICH COPIES STDIN TO STDOUT WITH THE LINE NUMBERS
*   ADDED. THE NUMBERS SHOULD BE LEFT-JUSTIFIED STARTING WITH COLUMN 1, AND
*   SHOULD BE SEPARATED FROM THE ACTUAL LISTING BY A SINGLE TAB.
*/

#include <stdio.h>

int main ()
{
    FILE *file;
    char c; 
    int lineNumber = 2; //line number
    file = fopen("test.c", "r"); //name of test file is test.c
    if (file == NULL) // if file is empty or dne, print an error
        perror ("Error Reading File");
    else
    {
        printf("1\t"); // start with line#1 followed with a tab
        do
        {
            c = getc (file); 
            printf("%c", c);//print each character of file
            if(c == '\n') // new line tells you when to start a new line
            {               
                printf("%d\t",lineNumber);//if new line, print number + tab
                lineNumber++;//increment line number
            }
        }
        while (c != EOF); // do until EOF
        fclose (file);//close file when EOF has been reached
    }
    printf("\n");
    return 0; 
}

