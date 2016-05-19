#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
    
    float change;
    int coins = 0;
    
    do {
    printf("How much change do I owe you?\n");
    change = GetFloat();
    }
    while(change < 0);
    
    float c = change * 100;
    c = round(c);
    float cents = (float) c; 
    
    while(cents >= 25){
        coins = coins + 1;
        cents = cents - 25;
    }
    while(cents >= 10){
        coins = coins + 1;
        cents = cents - 10;
    }
    while(cents >= 5){
        coins = coins + 1;
        cents = cents - 5;
    }
    while(cents >= 1){
        coins = coins + 1;
        cents = cents - 1;
    }
    
    printf("%d", coins);
    printf("\n");
}