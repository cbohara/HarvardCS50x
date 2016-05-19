#include <stdio.h>
#include <cs50.h>

int main(void){
    printf("minutes: ");
    int input = GetInt();
    int total = (input * 192) / 16;
    printf("bottles: %i", total);
    printf("\n");
}