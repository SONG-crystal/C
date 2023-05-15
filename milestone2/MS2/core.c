/*
*****************************************************************************
                        Assignment 1 - Milestone 2
Full Name  : SuJung Song
Student ID#: 174745218
Email      : ssong49@myseneca.ca
Section    : ipc144NEE

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>



// Copy the below commented "header" section to all your source code files!

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"





// As demonstrated in the course notes: 
//https://intro2c.sdds.ca/D-Modularity/input-functions#clearing-the-buffer
//Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}


// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


int inputInt(void)
{
    char newLine;
    int value, isPass = 1;

    do
    {
        scanf("%d%c", &value, &newLine);  
        if (newLine != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        else
        {
            isPass = 0;
        }


    } while (isPass);

    return value;
}


int inputIntPositive(void)
{
    int value2, isPass = 1;

    do
    {
        scanf("%d", &value2);
        if (value2 < 0)
        {
            printf("ERROR! Value must be > 0: ");  
            clearInputBuffer();
        }
        else
        {
            isPass = 0;

        }

    } while (isPass);

    return value2;
}


int inputIntRange(int low, int upp) 
{

    char newLine3;
    int value3, isPass = 1;

    do
    {
        scanf("%d%c", &value3, &newLine3);  
        
        if (newLine3 != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        else if (!(value3 >= low && value3 <= upp))
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", low, upp); 
            
        }                                                                           
        else
        {
            isPass = 0;
        }


    } while (isPass);

    return value3;
}


char inputCharOption(const char qwErty[])   
{

    char value5;
    int i = 0, isPass = 1;


    scanf("%c%*c", &value5);
    do
    {

        if (qwErty[i] != '\0')
        {
            if (qwErty[i] != value5)
            {
                i++;
            }
            else
            {
                isPass = 0;
            }
        }
        else
        {
            printf("ERROR: Character must be one of [%s]: ", qwErty);
            scanf("%c%*c", &value5);
            i = 0;
        }
    } while (isPass);

    return value5;
}




void inputCString(char* string, int min, int max)
{

    int i, stringLength = 0, isPass = 0;
    char userInput[1001];

    do
    {
        scanf("%1000[^\n]", userInput); 
        clearInputBuffer();

        i = 0;
        while (userInput[i] != '\0')
        {
            i++;
        }
        stringLength = i;



        if (stringLength >= min && stringLength <= max)
        {
            isPass = 1;
        }
        else
        {
            if (min == max)
            {
                printf("ERROR: String length must be exactly %d chars: ", max);
            }
            else if (stringLength > max)
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else if (stringLength < min || stringLength < max)
            {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
        }
    } while (!isPass);


    for (i = 0; i < max; i++)
    {
        string[i] = userInput[i];    // *(string+i)
    }

}





void displayFormattedPhone(const char* phoneNum)
{
    int i, text = 1;

    if (phoneNum == NULL)
    {
        printf("(___)___-____");
    }
    else
    {
        if (strlen(phoneNum) == 10)
        { 
            for (i = 0; i < 10 && text != 0; i++)
            {
                text = isdigit(phoneNum[i]);
            }

            if (text == 0)
            {
                printf("(___)___-____");
            }
            else
            {
                for (i = 0; i < 10; i++) {
                    if (i == 0) { printf("("); }
                    if (i == 3) { printf(")"); }
                    if (i == 6) { printf("-"); }
                    printf("%c", phoneNum[i]); 
                }
            }

        }
        else
        {
            printf("(___)___-____");
        }
    }

}