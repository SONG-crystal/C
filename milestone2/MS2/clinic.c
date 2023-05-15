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
#include <string.h>
#define MAX_PETS 7

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2); 
        putchar('\n');
        switch (selection)
        {
        case 0: 
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);    
            break;                                          
        case 2:                                             
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)  
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:                                         
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();                                   
            break;                                       
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN); 
            putchar('\n');                           
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone); 
            putchar('\n');
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}



void displayAllPatients(const struct Patient patient[], int max, int fmt) { 
   
    int i;

    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }
   

    for (i = 0; i < max; i++) 
    {
        if (patient[i].patientNumber != 0) 
        {
            displayPatientData(&patient[i], fmt);
        }      
    }
    putchar('\n');
}



// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max) {

    int selection, isPass=1;

    do 
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");

        scanf("%d", &selection);
        putchar('\n');
        switch (selection)
        {
        case 1: 
            searchPatientByPatientNumber(patient, max);  
            break;

        case 2:             
            searchPatientByPhoneNumber(patient, max); 
            break;
     
        case 0:
            isPass = 0;
            break;

        }
    } while (isPass);
}

// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max) 
{
    
    int i, count = 0;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber != 0) 
        {
            count++; 
        }
    }

    if (count == max) 
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else if (count != max)
    {
        (patient+count)->patientNumber = nextPatientNumber(patient, max); 


        inputPatient(&patient[count]); 

        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max) {

    int checkPatiNumber, i;

    printf("Enter the patient number: ");
    scanf("%d", &checkPatiNumber);
    clearInputBuffer();
    printf("\n");

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == checkPatiNumber)  
        {
            menuPatientEdit(&patient[i]);

        }
    }

}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max) {

    int checkPatiNumber, N;
    char answer;

    printf("Enter the patient number: ");
    scanf("%d", &checkPatiNumber);
    clearInputBuffer();
    printf("\n");

     N = findPatientIndexByPatientNum(checkPatiNumber, patient, max); 

     if (N == -1)
     {
         printf("ERROR: Patient record not found!\n\n");
     }
     else
     {
         displayPatientData(&patient[N], FMT_FORM); 
         printf("\n");
         printf("Are you sure you want to remove this patient record? (y/n): ");
         scanf("%c", &answer);
         clearInputBuffer();

         if (answer=='y') { 
             printf("Patient record has been removed!\n");
             patient[N].patientNumber = 0;  
             printf("\n");
         }
         else 
         {
             printf("Operation aborted.\n");
             printf("\n");
         }
     }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max) 
{

    int searchPatientNum, N;
    
    printf("Search by patient number: ");
    scanf("%d", &searchPatientNum);
    clearInputBuffer();
    putchar('\n');

    int i = 0, Pass = 1;
    while (Pass == 1 && i != max)
    {


        if (patient[i].patientNumber != searchPatientNum)
        {
            i++;
        }
        else if (patient[i].patientNumber == searchPatientNum)
        {
            N = i;
           
            displayPatientData(&patient[N], FMT_FORM);
            putchar('\n');
            suspend();
            Pass = 0;
        }
    }

    if (i == max) {
        printf("*** No records found ***");
        putchar('\n');
        putchar('\n');
        suspend();
    }
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
       int i, text=0;
       char searchPhoneNum[PHONE_LEN + 1];
    
       printf("Search by phone number: ");
       scanf("%s", searchPhoneNum);
       clearInputBuffer();

       putchar('\n');

       displayPatientTableHeader();



       int count = 0;
       for (i = 0; i < max; i++)
       {
           text = strcmp(patient[i].phone.number, searchPhoneNum);


           if (text == 0)
           {
               displayPatientData(&patient[i], FMT_TABLE);
           }
           else if (text != 0)
           {
               count++;
           }
       }

       if (count == max) {
           putchar('\n');
           printf("*** No records found ***");
           putchar('\n');
       }

       putchar('\n');
       suspend();

}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max) 
{
    int i, patientNumb=0;

    for (i = 0; i < max; i++) 
    {
        patientNumb = (patientNumb < (patient + i)->patientNumber) ? (patient + i)->patientNumber : patientNumb;  
    }                                                                          

    //printf("%d\n", patientNumb + 1); //1057 출력됨

   return  patientNumb+1;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) 
{
    int i, N = -1;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)  
        {
            N = i; 
        }
    }

    return N;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient) {// 비어있는 공간의 patient를 받았음
   
    char addPatientName[NAME_LEN + 1] = { 0 };
    
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: ");
    printf("%05d", patient->patientNumber); 
    printf("\n");                                             

    printf("Name  : ");
    scanf("%[^\n]", addPatientName); 
    clearInputBuffer();
    strcpy(patient->name, addPatientName); 
                                          
    printf("\n"); 
    inputPhoneData(&(*patient).phone); 
    printf("\n");                      
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone) {
   
    int N;
    char newNum[PHONE_LEN + 1];
    
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");     

    N = inputIntRange(1, 4);
    if (N == 4) 
    {
        strcpy(phone->description, "TBD");
    }
    else 
    {
        switch (N) {
        case 1:
            printf("\n"); 
            strcpy(phone->description, "CELL"); 
            printf("Contact: %s", phone->description);
            printf("\n");

            printf("Number : ");
            scanf("%s", newNum);
            clearInputBuffer();
            strcpy(phone->number, newNum);   
            break;

        case 2:
            printf("\n");
            strcpy(phone->description, "HOME");
            printf("Contact: %s", phone->description);
            printf("\n");

            printf("Number : ");
            scanf("%s", newNum);
            clearInputBuffer();
            strcpy(phone->number, newNum);
            break;

        case 3:
            printf("\n");
            strcpy(phone->description, "WORK");
            printf("Contact: %s", phone->description);
            printf("\n");

            printf("Number : ");
            scanf("%s", newNum);
            clearInputBuffer();
            strcpy(phone->number, newNum);
            break;
        }

    }
    



}