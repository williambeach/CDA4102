/*
*
William Beach
CDA4102 - Project 1, Program 1
Program that scans employee input and prints back the input
1/30/2023
*
*/

#include <stdio.h>

struct employee{
    char name[50];
    int age;
    float salary;
};

int main(){
    int i = 0;
    struct employee array[3];
    while (i < 3){
        printf("Please enter employee%d name: ", i + 1 );
        scanf("%s", array[i].name);
        printf("\n");
        printf("Please enter employee%d age: ", i + 1);
        scanf("%d", &array[i].age);
        printf("\n");
        printf("Please enter employee%d salary: ", i + 1);
        scanf("%f", &array[i].salary);
        printf("\n");
        i++;
    }
    for (i = 0; i < 3; i++){
        printf("Employee%d name: %s\n", i+1, array[i].name);
        printf("\n");
        printf("Employee%d age: %d\n", i+1,  array[i].age);
        printf("\n");
        printf("Employee%d salary: $%.2f\n", i+1, array[i].salary);
        printf("\n");
    }

    return 0;
}