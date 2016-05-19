#include <stdio.h>
#include <cs50.h>

int main(void){
    int height;
    
    do {
        printf("Height: ");
        height = GetInt();
    }
    while(height < 0 || height > 23);
    
    if(height > 0 && height <= 23){
        for(int row = 0; row < height; row++){
            
            for (int i = 0; i < (height - row - 1); i++){
                printf(" ");
            }
    
            for (int j = 0; j < (row + 2); j++){
                printf("#");
            }
            
            printf("\n");
        }
    }   
}