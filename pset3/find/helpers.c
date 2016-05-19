/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include "helpers.h"

/**
 * Sorts array of n values utilizing selection sort
 */
void sort(int values[], int n)
{
    // loop through the array of values 
    for(int i = 0; i < (n-1); i++){
        // set the current index as the minimum 
        int min = i;
        // loop through the array comparing the min index to the remaining elements in the array
        for(int j = (i + 1); j < n; j++){
           // compare each index value with the currently assigned minimum, and if the current index value is less than the current minimum, reassign the current index value to be the minimum index
           if(values[j] < values[min]){
               min = j;
           }
        }
        // if we reassigned the min in the previous step, we need to swap the minimum value with the first index value in the unsorted list
        if(min != i){
            int newMinValue = values[min];
            int oldMinValue = values[i];
            values[i] = newMinValue;
            values[min] = oldMinValue;
        }
    }
    return;
}

/**
 * Binary search returns true if value is in array of n values, else false.
 * O(log n) time is faster vs linear search, but the list must be ordered to implement binary search
*/
bool binarysearch(int value, int values[], int min, int max)
{
    if(min <= max){
        // save min, max, and middle values of original values[] array into variables
        int middle = (min + max)/ 2;
        
        // check the middle value of the array for target, and if found, return true
        if(values[middle] == value){
                return true;
        }
        // if the middle value is greater than the target, search the left half of the list for the target
        else if(value < values[middle]) {
            return binarysearch(value, values, min, middle-1);
        }
        // if the middle value is less than the target, search the right half of the list for the target
        else if(value > values[middle]){
            return binarysearch(value, values, middle+1, max);
        }
    }
    // if the value is not found, return false
    return false;
}

bool search(int value, int values[], int n)
{
    if(n < 0){
        return false;
    }
    // utilize recursive binary function
    return binarysearch(value, values, 0, n - 1);
}