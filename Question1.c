#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <semaphore.h>

int main(int argc, char *argv[]) {
    int numCustomers; // n customers
    int numResources; // m resource types
    for (int i = 0; i < argc; i++){
        printf("%s", argv[i]);
    }
    printf("Number of Cutsomers: ");
    scanf("%d", &numCustomers );
    return 0;
}