#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//must accept a single command-line argument: a keyword, k, composed entirely of alphabetical characters
int main(int argc, string argv[]){
    // if the program is executed without any command-line arguments or with more than one command-line argument, your program should yell at the user and return a value of 1
    if(argc != 2){
        printf("Please enter key!\n");
        return 1;
    }
    // command line input is stored as a string
    string key = argv[1];
    // store key length
    int keyLength = strlen(key);

    // first check that all chars in the key are alphabetical
    for(int i = 0; i < keyLength; i++){
        if(!isalpha(key[i])){
            printf("Please enter key containing only alphabetical letters!\n");
            return 1;
        }
    }
    
    // prompt the user for a string of plaintext 
    string plaintext = GetString();
    
    // create an array to store each alphabetical index value for each char key
    int keyAlphaIndexValue[keyLength];
    // iterate through key and convert from ASCII value to alphabetical index value
    for(int i = 0; i < keyLength; i++){
        // apply conversion for uppercase key char
        if(isupper(key[i])){
            keyAlphaIndexValue[i] = (key[i] - 65);
        }
        //apply conversion for lowercase key char
        else {
            keyAlphaIndexValue[i] = (key[i] - 97);
        }
    }
    
    // initialize key array value to the 0 index in order to loop through key within plaintext encryption
    int keyIndex = 0;
    // initialize iterator for key
    int k = 0;
    
    // iterate over each character in plaintext
    for(int i = 0, pLength = strlen(plaintext); i < pLength; i++) {
        // store current letter ASCII value
        int currentChar = plaintext[i];
        //initialize variables to store current alphabetical index value for current plaintext and key values
        int currentUpperAlpha;
        int currentLowerAlpha;
        int currentKeyAlpha;
        int convertBackToASCII;
        
        // if current char in plaintext is an alphabetical letter, apply encryption pattern on current char
        if(isalpha(currentChar)) {
            // determine key index value
            keyIndex = k % keyLength;

            // apply encryption formula for uppercase plaintext char
            if(isupper(currentChar)){
                // add plaintext and key alphabet index values and determine value within alphabet, then convert back to ASCII
                currentUpperAlpha = currentChar - 65;
                currentKeyAlpha = keyAlphaIndexValue[keyIndex];
                convertBackToASCII = ((currentUpperAlpha + currentKeyAlpha) % 26) + 97;
                printf("%c", toupper(convertBackToASCII));
                // increment key index to determine correct index value within key
                k++;
            }
            // apply encryption formula for lowercase plaintext char
            else {
                // add plaintext and key alphabet index values and determine value within alphabet, then convert back to ASCII
                currentLowerAlpha = currentChar - 97;
                currentKeyAlpha = keyAlphaIndexValue[keyIndex];
                convertBackToASCII = ((currentLowerAlpha + currentKeyAlpha) % 26) + 97;
                printf("%c", convertBackToASCII);
                // increment key index to determine correct index value within key
                k++;
            }
        } 
        
        // mirror original char if it is not an alphabetical char
        else {
            printf("%c", currentChar);
        }
    }
    printf("\n");
    // your program should exit, with main returning 0
    return 0;
}