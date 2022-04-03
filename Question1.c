#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>

int nCustomers, mResources = 4; // create global variables for both n amount of resources and n processes
int *available;                 // initalize resources pointer
int *safeSequence;              // initalize safe sequence
int **allocated;                // initalize allocated array
// int **max;                  // initalize max array
int **need; // initalize need array

int findSafeSequence(); // function to find the safe sequence, returns 1 if true, 0 if false

//  gcc Question1.c -o Question1
// ./Question1 10 5 7 8
int main(int argc, char *argv[])
{
    int i, j;
    char ch;
    FILE *fp = fopen("sample4_in.txt", "r");
    if (fp == NULL)
    {
        printf("file cannot be found\n");
    }

    printf("Number of Cutsomers: "); // request number of customers
    scanf("%d", &nCustomers);

    available = (int *)malloc((mResources) * sizeof(*available)); // allocate available as an array
    printf("Currently Available Resources: ");
    for (i = 0; i < nCustomers; i++)
    {
        if (i != 0)
        {
            sscanf(argv[i], "%d", &available[i - 1]);
            printf("%d ", available[i - 1]);
        }
    }
    printf("\n");

    allocated = (int **)malloc(nCustomers * sizeof(*allocated)); // create a 2d array for allocated, size nCustomers by mResources
    for (i = 0; i < nCustomers; i++)
        allocated[i] = (int *)malloc(mResources * sizeof(**allocated));

    // max = (int **)malloc(nCustomers * sizeof(*max)); // create a 2d array for max, size nCustomers by mResources
    // for (i = 0; i < nCustomers; i++)
    //     max[i] = (int *)malloc(mResources * sizeof(**max));

    // i = 0, j = 0;
    // printf("Maximum resources from file: \n");
    // while (!feof(fp)) // fill max with all the values in sample4_in.txt
    // {
    //     ch = fgetc(fp);
    //     // printf("%c", ch);
    //     if (isdigit(ch))
    //     {
    //         max[i][j] = ch - '0';
    //         printf("\n%d \n", max[i][j]);
    //         i++;
    //     }
    //     else if (strcmp(&ch, "\n") == 1)
    //     {
    //         j++;
    //         i = 0;
    //         printf("\n");
    //     }
    int max[5][4] = {{6, 4, 7, 3},
                     {4, 2, 3, 2},
                     {2, 5, 3, 3},
                     {6, 3, 3, 2},
                     {5, 5, 7, 5}};

    // }
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    // calculate the need matrix
    need = (int **)malloc(nCustomers * sizeof(*need)); // create a 2d array for need, size nCustomers by mResources
    for (i = 0; i < nCustomers; i++)
        need[i] = (int *)malloc(mResources * sizeof(**need));

    for (i = 0; i < nCustomers; i++)
    {
        for (j = 0; j < mResources; j++)
            need[i][j] = max[i][j] - allocated[i][j];
    }

    safeSequence = (int *)malloc(nCustomers * sizeof(*safeSequence)); // initalize an array of all -1 to change if the sequence is safe
    for (int i = 0; i < nCustomers; i++)
        safeSequence[i] = -1;

    char command[10];
    while (1)
    {
        printf("Enter Command: ");
        scanf("%s", command);
        if (strcmp(command, "Exit") == 0)
            break;

        else if (strcmp(command, "Run") == 0)
        {
            printf("run\n");
        }
        else if (strcmp(command, "Status") == 0)
        {
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
        }
        else if (strcmp(&command[0], "R") == 0 && strcmp(&command[1], "Q") == 0)
        {
            printf("requested\n");
        }
        else if (strcmp(&command[0], "R") == 0 && strcmp(&command[1], "L") == 0)
        {
            printf("leaving\n");
        }
    }
    free(available);
    for (i = i; i < nCustomers; i++)
    {
        // free(max[i]);
        free(need[i]);
        free(allocated[i]);
    }
    // free(max);
    free(need);
    free(allocated);
    return 0;
}

int findSafeSequence()
{
    int i, j, k;
    int tempAvailable[mResources];
    for (i = 0; i < mResources; i++)
    {
        tempAvailable[i] = available[i];
    }
    int finished[nCustomers]; // initalize an array to store if its checked each resource
    for (i = 0; i < nCustomers; i++)
        finished[i] = 1; // make each value start as false

    int nfinished = 0; // initalize a value to store how many times you check each resource
    while (nCustomers > nfinished)
    {
        int safety = 1; // initalize a value to change if the sequence is safe, default false

        for (i = 0; i < nCustomers; i++)
        {
            if (finished[i] = 1)
            {
                int tempSafety = 0; // a temporary saftey checker, default true
                for (j = 0; j < mResources; j++)
                {
                    if (need[i][j] > tempAvailable[i])
                    {
                        tempSafety = 1; // temp safety is false
                        break;
                    }
                }
                if (tempSafety == 0)
                {
                    for (j = 0; j < mResources; j++)
                    {
                        tempAvailable[j] += allocated[i][j];
                    }
                    safety = 0; // sequence is safe
                    finished[i] = 0;
                    nfinished++;
                    safeSequence[nfinished - 1] = i;
                }
            }
        }
        if (safety != 0)
        {
            for (k = 0; k < nCustomers; k++)
            {
                safeSequence[k] = -1;
            }
            return 1; // return false, sequence is not safe
        }
    }
    return 0; // return true, sequence is safe
}