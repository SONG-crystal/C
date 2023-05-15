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

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

#ifndef CORE_H
#define CORE_H


// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);






//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////
int inputInt(void);

int inputIntPositive(void);

int inputIntRange(int low, int upp);

char inputCharOption(const char qwErty[]);

void inputCString(char* input6, int intMin, int intMax);

void displayFormattedPhone(const char* phoneNum);








// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
