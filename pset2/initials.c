#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void){
    string name = GetString();
    
    //print first initial
    char first = toupper(name[0]);
    printf("%c", first);
    
    //find space in between first and last name and print first char of last name
    if(name != NULL){
        for(int i = 0, n = strlen(name); i < n; i++){
            if(name[i] == ' '){
                printf("%c", toupper(name[i + 1]));
            }
        }
    }
    printf("\n");
}