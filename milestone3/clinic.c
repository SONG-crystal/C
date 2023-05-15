/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  : SuJung Song
Student ID#: 17274518
Email      : ssong49@myseneca.ca
Section    : IPC144NEE

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt) 
{

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
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) {

    int selection, isPass = 1;

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
// (Copy your code from MS#2)
void addPatient(struct Patient *patient, int max) 
{
    int index;

    if (findPatientIndexByPatientNum(0, patient, max) != -1) 
    {
        index = findPatientIndexByPatientNum(0, patient, max);

        (patient+index)->patientNumber = nextPatientNumber(patient, max); 

        inputPatient(&patient[index]); 

        printf("*** New patient record added ***\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n"); 
    }

    printf("\n");


}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) { 

    int checkPatiNumber, N;
    char answer =0; 

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
        answer = inputCharOption("yn");

    }

    if (answer == 'y')
    {
        patient[N].patientNumber = 0;


        printf("Patient record has been removed!\n");
        printf("\n");
    }
    else if (answer == 'n')
    {
        printf("Operation aborted.\n");
        printf("\n");
    }
}


// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)  
{
    int i, index;

    sortData(data->appointments, &data->maxAppointments);
    displayScheduleTableHeader(&data->appointments->date, 1); 
    
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber != 0)
        {

            index = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
            
            if (index != -1)
            {
                displayScheduleData(&data->patients[index], &data->appointments[i], 1); 
            }
        }
    }
    putchar('\n');
}



void viewAppointmentSchedule(struct ClinicData* data)
{
    int i, index, dateDay = 0;
    struct Date date;

    printf("Year        : ");
    scanf("%d", &date.year);
    clearInputBuffer();

    printf("Month (1-12): ");
    scanf("%d", &date.month);
    clearInputBuffer();

    printf("Day (1-");
    if (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 10)
    {
        dateDay = 31;
    }
    else if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)
    {
        dateDay = 30;
    }
    else if (date.month == 2)
    {

        if (date.year % 4 == 0) 
        {
            dateDay = 29;
        }
        else if(date.year % 4 != 0) 
        {
            dateDay = 28;
        }
        
    }
    printf("%d)  : ", dateDay);
    
    scanf("%d", &date.day);
    clearInputBuffer();
    //printf("\n");

    while ((!(date.day >= 1 && date.day <= dateDay)) || (!(date.month >= 1 && date.month <= 12))) {
        if (!(date.day >= 1 && date.day <= dateDay))
        {
            printf("ERROR! Value must be between 1 and %d inclusive: ", dateDay);
            scanf("%d", &date.day);
            clearInputBuffer();
        }
        else if (!(date.month >= 1 && date.month <= 12)) {
            printf("ERROR! Value must be between 1 and 12 inclusive: ");
            scanf("%d", &date.month);
            clearInputBuffer();
        }
    }
    putchar('\n');

    sortData(data->appointments, data->maxAppointments);
    displayScheduleTableHeader(&date, 0);

    for (i = 0; i < data->maxAppointments; i++)
    {
        for (index = 0; index < data->maxPatient; index++)
        {
            if ((data->appointments[i].patientNumber == data->patients[index].patientNumber)
                && (date.year == data->appointments[i].date.year) && (date.month == data->appointments[i].date.month) && (date.day == data->appointments[i].date.day))
            {
                displayScheduleData(&data->patients[index], &data->appointments[i], 0);
            }
        }
    }
    printf("\n");
}

void addAppointment(struct Appointment *appointment, int maxA, struct Patient *patient, int maxP)
{
    int patientNumber, i, isPass=1, index=0;
    int isDate = 1, flag = 1, f=1;
    struct Date date = { 0 };
    struct Time time = { 0 };

    printf("Patient Number: ");
    scanf("%d", &patientNumber); 
    clearInputBuffer();

    if (findPatientIndexByPatientNum(patientNumber, patient, maxP) != -1) 
    {
        do {
            isDate = 0;
            printf("Year        : ");
            scanf("%d", &date.year);
            clearInputBuffer();

            printf("Month (1-12): ");
            scanf("%d", &date.month);
            clearInputBuffer();

            printf("Day (1-31)  : ");
            scanf("%d", &date.day);
            clearInputBuffer();

            do {
                isPass = 0;
                printf("Hour (0-23)  : ");
                scanf("%d", &time.hour);
                clearInputBuffer();

                printf("Minute (0-59): ");
                scanf("%d", &time.min);
                clearInputBuffer();

                if (((time.hour*100+time.min < 1000) || (time.hour * 100 + time.min > 1400)) || time.min % 30 != 0)
                {
                    printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n");
                    isPass = 1;
                }
                else
                { 
                    f = 1;
                    for (i = 0; f && i < maxA; i++) 
                    {  
                        if ((appointment[i].date.year == date.year)
                            && (appointment[i].date.month == date.month)
                            && (appointment[i].date.day == date.day)
                            && (appointment[i].time.hour == time.hour)
                            && (appointment[i].time.min == time.min))
                        {
                            printf("\nERROR: Appointment timeslot is not available!\n\n");
                            isPass = 0;
                            isDate = 1;
                            f = 0;
                        }
                        else
                        {
                            isDate = 0; 
                        }
                    }
                }
            } while (isPass);

        } while (isDate);


        for (i = 0; flag && i < maxA; i++)
        {
            if (appointment[i].patientNumber == 0) 
            {
                index = i;
                flag = 0;
            }
        }

        appointment[index].patientNumber = patientNumber;
        appointment[index].date = date;
        appointment[index].time = time;

        printf("\n*** Appointment scheduled! ***\n\n");
    }    
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
} 


void removeAppointment(struct Appointment* appointment, int maxA, struct Patient* patient, int maxP)
{
    int patientNumber, i = 0, f = 1, index = 0;
    char answer;
    struct Date date = { 0 };


    printf("Patient Number: ");
    scanf("%d", &patientNumber); 
    clearInputBuffer();




    if (findPatientIndexByPatientNum(patientNumber, patient, maxP) != -1)
    {
        printf("Year        : "); 
        scanf("%d", &date.year);
        clearInputBuffer();

        printf("Month (1-12): ");
        scanf("%d", &date.month);
        clearInputBuffer();

        printf("Day (1-29)  : ");
        scanf("%d", &date.day);
        clearInputBuffer();




        for (i = 0; f && i < maxA; i++)
        {
            if ((appointment[i].date.year == date.year) 
                && (appointment[i].date.month == date.month)
                && (appointment[i].date.day == date.day)
                &&(appointment[i].patientNumber == patientNumber))
            {
                index = i; 
                f = 0;     
                printf("\n");
                displayPatientData(&patient[findPatientIndexByPatientNum(patientNumber, patient, maxP)], FMT_FORM); // 이부분 이해안감 
            }
        }



        printf("Are you sure you want to remove this appointment (y,n): ");
        answer = inputCharOption("yn");
        printf("\n");


        if (answer == 'y')
        {
            appointment[index].patientNumber = 0;
      
            printf("Appointment record has been removed!\n\n");
        }
        else if (answer == 'n')
        {
            printf("Operation aborted.\n");
        }


    }
    else 
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

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


void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i, text = 0;
    int count = 0;
    char searchPhoneNum[PHONE_LEN + 1];

    printf("Search by phone number: ");
    scanf("%s", searchPhoneNum);
    clearInputBuffer();

    putchar('\n');

    displayPatientTableHeader();



   
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

int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, patientNumb = 0;


    for (i = 0; i < max; i++)
    {
        patientNumb = (patientNumb < (patient + i)->patientNumber) ? (patient + i)->patientNumber : patientNumb;  //&patient[i] 라고 처음에 생각함 
    }


    return  (patientNumb + 1);

}

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



void sortData(struct Appointment appointment[], int max) 
{

    int i, j;
    struct Appointment temp = { 0 };

    totalMinute(appointment, max);

    for (i = max - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (appointment[j].time.min > appointment[j + 1].time.min)
            {
                temp = appointment[j];
                appointment[j] = appointment[j + 1];
                appointment[j + 1] = temp;
            }
        }
    }

    nonTotalMinute(appointment, max);
}




void totalMinute(struct Appointment totalMin[], int max)
{
    int i;

    for (i = 0; i < max; i++)
    {
        totalMin[i].time.min += (totalMin[i].date.year * 525600) + (totalMin[i].date.day * 1440) + (totalMin[i].time.hour * 60);
    }

    if (totalMin[i].date.month == 1 || totalMin[i].date.month == 3 || totalMin[i].date.month == 5 || totalMin[i].date.month == 7 ||
        totalMin[i].date.month == 8 || totalMin[i].date.month == 10 || totalMin[i].date.month == 12)
    {
        totalMin[i].time.min += (totalMin[i].date.month * 44640);
    }
    else if (totalMin[i].date.month == 4 || totalMin[i].date.month == 6 || totalMin[i].date.month == 9 || totalMin[i].date.month == 11)
    {
        totalMin[i].time.min += (totalMin[i].date.month * 43200);
    }
    else if (totalMin[i].date.month == 2) 
    {
        if (totalMin[i].date.year % 4 == 0)   
        {
            totalMin[i].time.min += (totalMin[i].date.month * 40320);
        }
        else if (totalMin[i].date.year % 4 != 0)
        {
            totalMin[i].time.min += (totalMin[i].date.month * 41760);
        }
    }
}


void nonTotalMinute(struct Appointment nonTotalMin[], int max)
{
    int i;

    for (i = 0; i < max; i++)
    {
        nonTotalMin[i].time.min -= (nonTotalMin[i].date.year * 525600) + (nonTotalMin[i].date.day * 1440) + (nonTotalMin[i].time.hour * 60);
    }

    if (nonTotalMin[i].date.month == 1 || nonTotalMin[i].date.month == 3 || nonTotalMin[i].date.month == 5 || nonTotalMin[i].date.month == 7 ||
        nonTotalMin[i].date.month == 8 || nonTotalMin[i].date.month == 10 || nonTotalMin[i].date.month == 12)
    {
        nonTotalMin[i].time.min -= (nonTotalMin[i].date.month * 44640);
    }
    else if (nonTotalMin[i].date.month == 4 || nonTotalMin[i].date.month == 6 || nonTotalMin[i].date.month == 9 || nonTotalMin[i].date.month == 11)
    {
        nonTotalMin[i].time.min -= (nonTotalMin[i].date.month * 43200);
    }
    else if (nonTotalMin[i].date.month == 2) //2월일때 기준으로 나누기 
    {
        if (nonTotalMin[i].date.year % 4 == 0)   
        {
            nonTotalMin[i].time.min -= (nonTotalMin[i].date.month * 40320);
        }
        else if (nonTotalMin[i].date.year % 4 != 0)
        {
            nonTotalMin[i].time.min -= (nonTotalMin[i].date.month * 41760);
        }
    }
}





//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) {

    //char addPatientName[NAME_LEN + 1] = { 0 };


    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: ");
    printf("%05d", patient->patientNumber); 
    printf("\n");

    printf("Name  : ");
    inputCString(patient->name, 0, NAME_LEN); 


    printf("\n");
    inputPhoneData(&(*patient).phone);
    printf("\n");
}

void inputPhoneData(struct Phone* phone) {

    int N;
    char newNum[20] = {0}; 

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

            do {
                if (strlen(newNum) != 10)
                {
                    printf("Invalid 10-digit number! Number: ");
                    scanf("%s", newNum);  
                    clearInputBuffer();
                }
            } while (strlen(newNum) != 10); 

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

            do {
                if (strlen(newNum) != 10)
                {
                    printf("Invalid 10-digit number! Number: ");
                    scanf("%s", newNum);
                    clearInputBuffer();
                }
            } while (strlen(newNum) != 10);  

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

            do {
                if (strlen(newNum) != 10)
                {
                    printf("Invalid 10-digit number! Number: ");
                    scanf("%s", newNum);
                    clearInputBuffer();
                }
            } while (strlen(newNum) != 10); 

            strcpy(phone->number, newNum);   
            break;
        }

    }
}




int importPatients(const char* datafile, struct Patient patients[], int max)
{
    FILE* ptr = NULL;

    int i = 0;

    ptr = fopen(datafile, "r");

    if (ptr != NULL)
    {
        while ((i < max) && fscanf(ptr, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number) != EOF)
        {
            i++;
        } 
    }
    fclose(ptr);

    return i; 
}


int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    FILE* ptr = NULL;

    int i = 0;

    ptr = fopen(datafile, "r");

    if (ptr != NULL)
    {
        while ((i < max) && fscanf(ptr, "%d, %d, %d,%d,%d, %d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) != EOF)
        {
            i++;
        }
    }
    fclose(ptr);

    return i;
}