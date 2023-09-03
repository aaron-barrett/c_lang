#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

void push(char* stack, int* top, char data){
    if(*top == MAX-1){
        printf("Error: Stack is full\n");
        return;
    }
    (*top)++;
    stack[*top] = data;
}

char pop(char* stack, int* top){
    if(*top == -1){
        printf("Error: Stack is empty.\n");
        return ' ';
    }
    char data = stack[*top];
    (*top)--;
    return data;
}



int main(){

    char stack[MAX];
    int top = -1;

    push(stack, &top, 'k');
    push(stack, &top,'c');
    push(stack, &top,'a');
    push(stack, &top,'t');
    push(stack, &top,'s');

    while(top != -1)
        printf("%c", pop(stack, &top));

    return 0;
}
