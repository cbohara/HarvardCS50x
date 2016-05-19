/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // instruct the user that the program requires at least one command-line argument
    // n = how many psuedorandom numbers the program should genereate
    // the user may also specify a seed value (an input to a pseudorandom-number generator that influences its outputs)
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // save command-line argument n into a variable
    int n = atoi(argv[1]);

    // if the user also specified a seed value, utilize the srand48 function in order to obtain the same 
    // list of numbers when the program input is the same seed value
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // utilize the drand48() function to generate a list of pseudorandom numbers, with its length determined
    // by the size of n
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}