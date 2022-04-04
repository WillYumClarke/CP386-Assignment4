#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>

void allocate();
void release();

struct Process {
    int allocated;
    int beg;
    int end;
};

int main(int argc, char *argv[])
{
    int MAX;
    sscanf(argv[1], "%d", &MAX);
    int memory[MAX];
    for (int i=0; i<MAX; i++){ // the memory array will store a value of -1 if it is free, 0 if it is used by process 0, 1 if by process 1 and so on
        memory[i] = -1;
    }
    int allocatedMem = 0;
    printf("Allocated %d bytes of memory\n", MAX);
    char *command;
    char *algo;
    size_t len = 0;
    ssize_t read = 0;
    char process[1];
    int mem, prev = -1, curr, beg = 0, end = 0;
    while (1)
    {
        printf("command>");
        getline(&command, &len, stdin);
        if (strncmp(command, "Exit", 3) == 0)
            break;
        else if (strncmp(command, "Status", 6))
        {
            // printf("Partitions [Allocated memory = %d", allocatedMem);
            // int i=0,j=0,k=0;
            // if (memory[0] == -1){
            //     while memory[0] = -1{
            //         i++;
            //     }
            // }
            // beg = i;
            // prev = memory[beg+1]; 
            // for (i; i<max; i++){

            // }
        }
        else if (strncmp(command, "RQ", 2) == 0)
        {
            sscanf(&command[3], "%c", &process[0]);
            sscanf(&command[4], "%c", &process[1]);
            sscanf(&command[6], "%d", &mem);
            sscanf(&command[len - 1], "%c", algo);
            // printf("process: %s\n", process);
            // printf("mem: %d\n", mem);
            // printf("algo: %s\n", algo);
        }
        else if (strncmp(command, "RL", 2) == 0)
        {
            sscanf(&command[3], "%c", &process[0]);
            sscanf(&command[4], "%c", &process[1]);
        }
    }
}