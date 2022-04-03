#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>

int nCustomers, mResources; // create global variables for both n amount of resources and n processes
int *available;             // initalize resources pointer
int *safeSequence;          // initalize safe sequence
int **allocated;            // initalize allocated array
// int **max;                  // initalize max array
int **need; // initalize need array

void *runCode(void *);  // function to run the user entered code
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
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    //calculate the need matrix
    need = (int **)malloc(nCustomers * sizeof(*need)); // create a 2d array for need, size nCustomers by mResources
    for (i = 0; i < nCustomers; i++)
        need[i] = (int *)malloc(mResources * sizeof(**need));

    for (i = 0; i < nCustomers; i++)
    {
        for (j = 0; j < mResources; j++)
            need[i][j] = max[i][j] - allocated[i][j];
    }
    return 0;
}