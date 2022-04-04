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

struct Process
{
    int pNum;      // process number
    int allocated; // amount of memory allocated
    int beg;       // begining of memory allocated
    int end;       // end of memory allocated
};

struct Process *P1 = NULL;
struct Process *P2 = NULL;
struct Process *P3 = NULL;
struct Process *P4 = NULL;

void status(struct Process *ProcessArray[4]);
void release(char command[], struct Process *ProcessArray[4]);
void request(char command[], struct Process *ProcessArray[4]);

int MAX, available; // global variables
int main(int argc, char *argv[])
{
    struct Process *ProcessArray[4];
    // ProcessArray[0] = P1;
    // ProcessArray[1] = P2;
    // ProcessArray[2] = P3;
    // ProcessArray[3] = P4;

    sscanf(argv[1], "%d", &MAX);
    available = MAX;

    printf("Allocated %d bytes of memory\n", MAX);

    char command[20];
    char RQ[3] = "RQ ";
    char RL[3] = "RL ";
    printf("command>");
    scanf(" %[^\n]", command);
    while (strcmp(command, "Exit") != 0)
    {
        if (strncmp(command, "Status", 2) == 0)
        {
            status(ProcessArray);
        }
        else if (strncmp(command, RQ, 2) == 0)
        {
            request(command, ProcessArray);
        }
        else if (strncmp(command, RL, 2) == 0)
        {
            release(command, ProcessArray);
        }
        printf("Enter Command: ");
        scanf(" %[^\n]", command);
    }
    return 0;
}

void status(struct Process *ProcessArray[4])
{
    int i = 0, j = 0;
    printf("Partitions [Allocated memory = %d]:\n", MAX - available);
    while (i < 4)
    {
        if (ProcessArray[i] != NULL)
        {
            printf("Address [%d:%d] Process of P%d\n", ProcessArray[i]->beg, ProcessArray[i]->end, ProcessArray[i]->pNum);
        }
        i++;
    }
    printf("Holes [Free memory = %d]:\n", available);
    while (j < 4)
    {
        if (ProcessArray[i] == NULL)
        {
            if (j == 0)
                printf("Address [0:%d] len = %d\n", ProcessArray[j + 1]->beg - 1, ProcessArray[j + 1]->beg);
            else if (j != 1 && j != 3)
                printf("Address [%d:%d] len = %d\n", ProcessArray[j - 1]->end + 1, ProcessArray[j + 1]->beg - 1, (ProcessArray[j + 1]->beg - 1) - (ProcessArray[j - 1]->end + 1));
            else
            {
                printf("Address [%d:%d] len = %d\n", ProcessArray[j - 1]->end - 1, MAX - 1, MAX - (ProcessArray[j - 1]->end - 1));
            }
        }
        j++;
    }
    return;
}

void request(char command[], struct Process *ProcessArray[4])
{
    int i;
    int memReq, pNumReq;
    char *token = strtok(command, " ");
    for (i = 0; i < 4; i++)
    {
        if (i == 1)
        {
            pNumReq = token[1] - '0';
        }
        if (i == 2)
            memReq = atoi(token);
        token = strtok(NULL, " ");
    }
    if (available < memReq)
        printf("No hole of sufficient size\n"); // thats what she said
    else
    {
        for (i = 0; i < 4; i++)
        {
            if (ProcessArray[i] == NULL)
            {
                if (i == 0)
                {
                    ProcessArray[i]->pNum = pNumReq;
                    ProcessArray[i]->beg = 0;
                    ProcessArray[i]->end = memReq;
                    ProcessArray[i]->allocated = memReq;
                }
                else
                {
                    ProcessArray[i]->pNum = pNumReq;
                    ProcessArray[i]->beg = ProcessArray[i - 1]->end + 1;
                    ProcessArray[i]->end = ProcessArray[i]->beg + memReq;
                    ProcessArray[i]->allocated = memReq;
                }
            }
        }
        printf("Sucessfully allocated %d to process P%d\n", memReq, pNumReq);
    }
    return;
}

void release(char command[], struct Process *ProcessArray[4])
{
    int i;
    int pNumRel;
    char *token = strtok(command, " ");
    for (i = 0; i < 4; i++)
    {
        if (i == 1)
        {
            pNumRel = token[1] - '0';
        }
        token = strtok(NULL, " ");
    }
    for (i = 0; i < 4; i++)
    {
        printf("%d\n", i);
        if (ProcessArray[i] != NULL)
        {
            if (pNumRel == ProcessArray[i]->pNum)
            {
                printf("releasing memory for process P%d\n", pNumRel);
                ProcessArray[i]->beg = 0;
                ProcessArray[i]->end = 0;
                ProcessArray[i]->allocated = 0;
                ProcessArray[i]->pNum = 0;
                ProcessArray[i] = NULL;
                printf("Sucessfully released memory for process P%d\n", pNumRel);
                break;
            }
        }
    }
    return;
}