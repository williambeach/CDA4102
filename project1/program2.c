/*
*
William Beach
CDA4102 - Project 1, Program 2
Program that reads in 6 numbers from standard input and outputs min, max, avg, and sum. 
1/30/2023
*
*/



#include <stdio.h>

int main(){
    int intArray[6];
    short i;
    float min, max, avg, sum = 0;
    
    for (i = 0; i < 6; i++){
        printf("Please enter number %d/6: ", i + 1);
        scanf("%d", &intArray[i]);
        printf("\n");
    }

    min = intArray[0];
    max = intArray[0];
    for (i = 0; i < 6; i++){
        if (intArray[i] < min){
            min = intArray[i];
        }
        if (intArray[i] > max){
            max = intArray[i];
        }
        sum += intArray[i];
    }

    avg = sum / 6;
    
    printf("Min: %.2f\n", min);
    printf("Max: %.2f\n", max);
    printf("Average: %.2f\n", avg);
    printf("Sum: %.2f\n", sum);

    return 0;
}