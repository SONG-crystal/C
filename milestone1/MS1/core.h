#pragma once


/*
*****************************************************************************
                        Assignment 1 - Milestone 1
Full Name  : SuJung Song
Student ID#: 172745218
Email      : ssong49@myseneca.ca
Section    : IPC144NEE

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

// Clear the standard input buffer
void clearInputBuffer(void);

// Wait for user to input the "enter" key to continue
void suspend(void);

int inputInt(void);

int inputIntPositive(void);

int inputIntRange(int low, int upp);

char inputCharOption(const char qwErty[]);

void inputCString(char* input6, int intMin, int intMax);

void displayFormattedPhone(const char* phoneNum); 


