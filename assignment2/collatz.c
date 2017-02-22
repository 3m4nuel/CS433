#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define REQ_ARG_COUNT 2
#define INT_ARG 1

/* Method to handle actual errors */
void error(const char *errorMsg)
{
    perror(errorMsg);
    exit(EXIT_FAILURE);
}

/* Check whether the integer is even or odd */
int isEven(int value)
{
    if(value % 2 == 0)
        return 1;
    else
        return 0;
}

/* Uses Collatz Conjecture formula when integer is even */
int evenCollatzConjecture(int curValue)
{
    return curValue / 2;
}

/* Uses Collatz Conjecture formula when integer is odd */
int oddCollatzConjecture(int curValue)
{
    return 3 * curValue + 1;
}

/* Child process method: uses recursion to display Collatz Conjecture calculation */
void runChildProcess(int intToProcess)
{
    /* Loops through Collatz Conjecture until the expected ended value of 1 */
    while(intToProcess > 1)
    {
        if(isEven(intToProcess) == 1)
            intToProcess = evenCollatzConjecture(intToProcess);
        else
            intToProcess = oddCollatzConjecture(intToProcess);

        printf("CHILD: Current value = %d \n", intToProcess);
    }
}

/* Parent process method: waits for child process to end */
void runParentProcess()
{
    pid_t cmpPid;
    int status;
    cmpPid = wait(&status);

    if(status != 0) {
        /* Verifies expected return value of 0 is returned. */
        error("ERROR: Child process ended incorrectly");
    }

    printf("PARENT: Process %d ended with status %d\n", cmpPid, status);
}

int main(int argc,  char **argv)
{
    int intToProcess, argumentIndex = 0;
    pid_t childPid;

    if(argc != REQ_ARG_COUNT) {
        /* Verifies only expected number of arguments are set. */
        printf("ERROR: Invalid argument count.\n");
        return -1;
    }

    /* Verifies a non-zero integer argument is inputted. */
    while(argv[INT_ARG][argumentIndex])
    {
        if(isalpha(argv[INT_ARG][argumentIndex]) || argv[INT_ARG][argumentIndex] == '.') {
            printf("ERROR: Argument must be an integer.\n");
            return -1;
        }
        argumentIndex++;
    }

    /* Converts user input into integer for processing. */
    intToProcess = atoi(argv[INT_ARG]);

    if ((childPid = fork()) < 0) {
       /* Fork command failed - check the error. */
       error("ERROR: fork failed.\n");
    }
    else if (childPid == 0) {
        runChildProcess(intToProcess);
    }
    else {
        runParentProcess();
    }

    return 0;
}
