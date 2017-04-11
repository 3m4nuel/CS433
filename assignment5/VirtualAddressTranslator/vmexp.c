/*
 * Emmanuel A. Castillo
 * 004268444
 * Operating Systems
 * Programming Assignment 5:
 * -----------------------------------------
 * Synchronize threads in accessing data
 * from a memory block using mutex and
 * counting semaphores. A seperate empty and full
 * counting semaphore is used to determine whether
 * a producer has space to write or a consumer
 * has data to read. The mutex implements mutual
 * exclusion among the shared memory block
 * so the producer and consumer can properly
 * synchronize their write and read
 * operations, respectively. Additionally,
 * a checksum is used on the last 2 bytes of
 * each 32 bytes block to validate the data.
 *
 * Compiling:
 * -----------------------------------------
 * gcc vmexp.c -o vmexp
 *
 *
 * Output with argument of <address>: 19986
 * -----------------------------------------
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    /* Command line index incremeter */
    int argumentIndex = 0;

    /* Variables to handle address translation */
    unsigned long address;
    unsigned long page;
    unsigned long offset;


    /* Verify the comand line parameters */
    if (argc != 2 ) {
       printf("Usage: %s <address> \n", argv[0]);
       exit( -1);
    }

    /* Verify the address value is a valid decimal */
    while(argv[1][argumentIndex])
    {
        if(!isdigit(argv[1][argumentIndex])) {
            printf("Error: <address> must be a non-negative decimal.\n");
            exit( -1);
        }
        argumentIndex++;
    }

    /* Set address variable from input into correct data type */
    address = atoll(argv[1]);

    /* Obtain both page and offset from input address */
    page = address >> 12; // Page size is based on 4KB, thus 12 bits
    offset = address & 0xfff; // Reminader defines the offset

    /* Dispay results to console */
    printf("The address %lu contains: \n", address);
    printf("page number = %lu\n", page);
    printf("offset = %lu\n", offset);

    return 0;
}
