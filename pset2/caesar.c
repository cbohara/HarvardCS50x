#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// a program that encrypts messages using Caesar’s cipher must accept a single command-line argument: a non-negative integer (k)
int main(int argc, string argv[]){
    // if the program is executed without any command-line arguments or with more than one command-line argument, your program should yell at the user and return a value of 1
    if(argc != 2){
        printf("Please enter key value!\n");
        return 1;
    }
    // user input is stored as a string, so convert to an int using atoi function
    int k = atoi(argv[1]);
    
    // prompt the user for a string of plaintext 
    string p = GetString();

    // iterate over characters of the input string then output that text with each alphabetical character 
    // "rotated" by k positions; non-alphabetical characters should be outputted unchanged
    for(int i = 0, n = strlen(p); i < n; i++) {
        // store current letter ASCII value
        int currentChar = p[i];
        // if current char in string is an alphabetical letter, apply encryption pattern
        if(isalpha(currentChar)) {
            // apply appropriate encryption formula for uppercase vs lowercase char value
            if(isupper(currentChar)){
                printf("%c", (((currentChar + k) - 65) % 26) + 65);
            }
            else
                printf("%c", (((currentChar + k) - 97) % 26) + 97);
        } 
        // if char is not in the alphabet, do not alter
        else {
            
            printf("%c", currentChar);
        }
    }
    printf("\n");
    // your program should exit, with main returning 0
    return 0;
}