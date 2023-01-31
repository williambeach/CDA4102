/*
*
William Beach
CDA 4102 - Project 1, Program 3
Program that takes in names and swaps them and prints them to std output
1/30/2023
*
*/

#include <stdio.h>
#include <string.h>

int main(){
    char name1[50], name2[50], temp[50];
    printf("Please enter name: ");
    scanf("%s", name1);
    printf("\n");
    printf("Please enter name: ");
    scanf("%s", name2);
    printf("\n");
    printf("Names before swapping: %s %s", name1, name2);
    printf("\n");
    strcpy(temp, name1);
    strcpy(name1, name2);
    strcpy(name2, temp);
    printf("Names after swapping: %s %s", name1, name2);
    return 0;
}