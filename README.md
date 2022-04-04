# CP386-Assignment4

# Makefile
```CC = gcc
CFLAGS =  -Wall -g -std=gnu99
LDFLAGS = -lrt -lpthread 
TARGET = Question1 Question2 
OBJFILES = Question1.o Question2.o 
all: $(TARGET)
Question1: Question1.c
	$(CC) $(CFLAGS) -o Question1 Question1.c $(LDFLAGS)
Question2: Question2.c
	$(CC) $(CFLAGS) -o Question2 Question2.c $(LDFLAGS)

runq1: Question1
	./Question1 10 5 7 8
runq2: Question
	./Question2 1000000
clean:
	rm -f $(OBJFILES) $(TARGET) *~```

# Screenshots

# Individual Contribution
>All functions were written by myself, I originally had a partner but the prof seperated us due to me having evidence
that I sent him my project files for the first half of the assignment a week before it was dueand him never doing
the second half or handing anything in, so please be gracious since I had double the work 

# Feature
>main:    Initalizes all variables and  contains main loop
>findSafeSequence:    Finds the safe sequence if there is one
>request:    Processes a users request for resources
>release:    releases resources
>status:    prints the current status
run:    runs the user entered commands

# Test Cases

# Use Examples
```Number of Cutsomers: 5
Currently Available Resources: 10 5 7 8 
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 5 7 5 
Enter Command: RQ 0 1 0 0 1
State is safe, and request is satisfied
Enter Command: RQ 1 1 1 1 1
State is safe, and request is satisfied
Enter Command: RQ 2 2 2 2 2
State is safe, and request is satisfied
Enter Command: RQ 3 1 1 1 1
State is not safe, and request is not satisfied
Enter Command: RQ 4 1 0 0 0
State is not safe, and request is not satisfied
Enter Command: RQ 4 0 0 0 1
State is safe, and request is satisfied
Enter Command: Status
Available Resources:
3 1 4 5 
Maximum Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 5 7 5 
Allocated Resources:
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
0 0 0 0 
Need Resources:
6 4 7 3 
4 2 3 2 
2 5 3 3 
6 3 3 2 
5 5 7 5 
Enter Command: Run
Safe Sequence is: 1 3 2 4 0
--> Customer/Thread 0
    Allocated resources: 0 0 0 0
    Needed: 6 4 7 3
    Available:  3 1 4 5
    Thread has started
    Thread has finished
    Thread is releasing resources;    New Available: 3 1 4 5
--> Customer/Thread 1
    Allocated resources: 0 0 0 0
    Needed: 4 2 3 2
    Available:  3 1 4 5
    Thread has started
    Thread has finished
    Thread is releasing resources;    New Available: 3 1 4 5
--> Customer/Thread 2
    Allocated resources: 0 0 0 0
    Needed: 2 5 3 3
    Available:  3 1 4 5
    Thread has started
    Thread has finished
    Thread is releasing resources;    New Available: 3 1 4 5
--> Customer/Thread 3
    Allocated resources: 0 0 0 0
    Needed: 6 3 3 2
    Available:  3 1 4 5
    Thread has started
    Thread has finished
    Thread is releasing resources;    New Available: 3 1 4 5
--> Customer/Thread 4
    Allocated resources: 0 0 0 0
    Needed: 5 5 7 5
    Available:  3 1 4 5
    Thread has started
    Thread has finished
    Thread is releasing resources;    New Available: 3 1 4 5```

# About Developers
William Clarke
190524800
clar5248@mylaurier.ca