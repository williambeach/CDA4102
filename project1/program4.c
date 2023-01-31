/*
*
William Beach
CDA4102 - Project 1, Program 4
Pointer practice
1/30/23
*
*/

#include <stdio.h>

int main(){
    int myVariable = 4;
    int *myPtr = &myVariable;
    printf("The address of myPtr is: %d\n", &myPtr);
    printf("The value that myPtr points to is: %d\n", *myPtr);
    myVariable = 10;
    printf("The address of myPtr is: %d\n", &myPtr);
    printf("The value that myPtr points to is: %d\n", *myPtr);
    return 0;
}