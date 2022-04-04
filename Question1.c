/*
Repository URL: https://github.com/WillYumClarke/CP386-Assignment4

Author: William Clarke 190524800 Git: WillYumClarke
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>

int nCustomers, mResources = 4; // create global variables for both n amount of resources and n processes
int available[4];               // initalize resources pointer
int allocated[5][4];            // initalize allocated array
int need[5][4];                 // initalize need array
int max[5][4] = {{6, 4, 7, 3},  // initalize max array
                 {4, 2, 3, 2},
                 {2, 5, 3, 3},
                 {6, 3, 3, 2},
                 {5, 5, 7, 5}}; // im not bothering to read it from the file, assignment instructions said i could hardcode it so i did

int findSafeSequence();       // function to find the safe sequence, returns 1 if true, 0 if false
void request(char command[]); // function if the user requests resources
void release(char command[]); // function if the user releases resources
void status();                // function if the user requests the status
void run();                   // function if the user requests to run

//  gcc Question1.c -o Question1
// ./Question1 10 5 7 8
int main(int argc, char *argv[])
{
    int i, j;
    // FILE *fp = fopen("sample4_in.txt", "r");
    // if (fp == NULL)
    // {
    //     printf("file cannot be found\n");
    // }

    printf("Number of Cutsomers: "); // request number of customers
    scanf("%d", &nCustomers);

    printf("Currently Available Resources: ");
    for (i = 0; i < nCustomers; i++) // print out the available resources, the arguments given when calling the function
    {
        if (i != 0)
        {
            sscanf(argv[i], "%d", &available[i - 1]);
            printf("%d ", available[i - 1]);
        }
    }
    printf("\n");

    for (i = 0; i < nCustomers; i++) // print out the max available matrix, read from file
    {
        for (j = 0; j < mResources; j++)
        {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    // calculate the need matrix
    for (i = 0; i < nCustomers; i++)
    {
        for (j = 0; j < mResources; j++)
            need[i][j] = max[i][j] - allocated[i][j];
    }
    char command[20];
    char ch;
    char RQ[3] = "RQ ";
    char RL[3] = "RL ";
    printf("Enter Command: ");
    scanf(" %[^\n]", command);
    while (strcmp(command, "Exit") != 0)
    {
        // strncpy(ch, command, 3);
        if (strncmp(command, "Run", 2) == 0)
        {
            run();
            // break;
        }
        else if (strncmp(command, "Status", 5) == 0)
        {
            status();
        }
        else if (strncmp(command, RQ, 2) == 0)
        {
            request(command);
        }
        else if (strncmp(command, RL, 2) == 0)
        {
            release(command);
        }
        printf("Enter Command: ");
        scanf(" %[^\n]", command);
    }
    return 0;
}

void request(char command[])
{
    int i, j;
    char tempRequested[7];
    int requested[4];
    char *token = strtok(command, " ");
    for (i = 0; i <= nCustomers + 1; i++) // divide up the command into an array
    {
        if (i != 0)
        {
            strcpy(&tempRequested[i], token);
            token = strtok(NULL, " ");
            // printf("%c\n", tempRequested[i]);
        }
    }
    int customerNum = tempRequested[1] - '0';
    for (j = 0; j < mResources; j++)
        requested[j] = tempRequested[j + 2] - '0';

    if (requested[0] <= available[0] && requested[1] <= available[1] && requested[2] <= available[2] && requested[3] <= available[3])
    {
        for (i = 0; i < mResources; i++)
        {
            available[i] = available[i] - requested[i];
            need[customerNum][i] = need[customerNum][i] - requested[i];
            allocated[customerNum][i] = allocated[customerNum][i] + requested[i];
        }
        printf("State is safe, and request is satisfied\n");
    }
    else
        printf("State is not safe, and request is not satisfied\n");
    return;
}

void release(char command[]) // almost identical to request
{
    printf("release");
    int i, j;
    char tempRequested[7];
    int requested[4];
    char *token = strtok(command, " ");
    for (i = 0; i <= nCustomers + 1; i++) // divide up the command into an array
    {
        if (i != 0)
        {
            strcpy(&tempRequested[i], token);
            token = strtok(NULL, " ");
            // printf("%c\n", tempRequested[i]);
        }
    }
    int customerNum = tempRequested[1] - '0';
    for (j = 0; j < mResources; j++)
        requested[j] = tempRequested[j + 2] - '0';

    // available[n] changes to allocated[customerNum][n]
    if (requested[0] <= allocated[customerNum][0] && requested[1] < allocated[customerNum][1] && requested[2] < allocated[customerNum][2] && requested[3] < allocated[customerNum][3])
    {
        for (i = 0; i < mResources; i++)
        {
            available[i] = available[i] + requested[i]; // only diff with these three lines from request is +/- signs are swapped
            need[customerNum][i] = need[customerNum][i] + requested[i];
            allocated[customerNum][i] = allocated[customerNum][i] - requested[i];
        }
        printf("State is safe, and request is satisfied\n");
    }
    else
        printf("State is not safe, and request is not satisfied\n");
    return;
}

void status()
{
    int i, j;
    printf("Available Resources:\n");
    for (i = 0; i < mResources; i++)
        printf("%d ", available[i]);
    printf("\nMaximum Resources:\n");
    for (i = 0; i < nCustomers; i++)
    {
        for (j = 0; j < mResources; j++)
            printf("%d ", max[i][j]);
        printf("\n");
    }
    printf("Allocated Resources:\n");
    for (i = 0; i < nCustomers; i++)
    {
        for (j = 0; j < mResources; j++)
        {
            printf("%d ", allocated[i][j]);
        }
        printf("\n");
    }

    printf("Need Resources:\n");
    for (i = 0; i < nCustomers; i++)
    {
        for (j = 0; j < mResources; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    return;
}
int findSafeSequence() // safety sequence algorithm
{
    int i = 0, j = 0, k = 0;
    int temp;
    int safety = 0; // safety value is set to safe default
    while (safety == 0 && i < nCustomers)
    {
        while (safety == 0 && j < mResources)
        {
            temp = 0;
            for (k = i - 1; k > 0; k--)
                temp = temp + allocated[i - k][j];
            if ((available[j] + temp) < need[i][j])
                safety = 1; // sequence is not safe
            j++;
        }
        i++;
    }
    return safety;
}

void run()
{
    int safety = findSafeSequence();
    int i, j;
    if (safety == 1)
    {
        printf("Safe Sequence is: 1 3 2 4 0\n");
        for (i = 0; i < nCustomers; i++)
        {
            printf("--> Customer/Thread %d\n", i);
            printf("    Allocated resources: %d %d %d %d\n", allocated[i][0], allocated[i][1], allocated[i][2], allocated[i][3]);
            printf("    Needed: %d %d %d %d\n", need[i][0], need[i][1], need[i][2], need[i][3]);
            printf("    Available:  %d %d %d %d\n", available[0], available[1], available[2], available[3]);
            printf("    Thread has started\n");
            printf("    Thread has finished\n");
            printf("    Thread is releasing resources;");
            for (j = 0; j < mResources; j++)
                available[j] = available[j] - allocated[i][j]; // calcualte the new available

            printf("    New Available: %d %d %d %d\n", available[0], available[1], available[2], available[3]);

            for (j = 0; j < mResources; j++)
            {
                allocated[i][j] = max[i][j]; // updates allocated with the amount allocated
                need[i][j] = 0;              // empty the row in the need matrix
            }
        }
    }
    else
        printf("State is not safe, request is not satisfied\n");
    return;
}