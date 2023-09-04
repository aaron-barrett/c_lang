#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct stack stack;
void push_odd(stack*,char);
char pop_odd(stack*);
void push_even(stack*,char);
char pop_even(stack*);
struct stack{
    char* data;
    int top;
    int bottom;
};

stack* init_stack(){
    stack* a = malloc(sizeof(stack));
    a->data = malloc(sizeof(char)*MAX);
    a->top = -1;
    a->bottom = 0;
    return a;
}

void free_stack(stack* a){
    free(a->data);
    free(a);
}

void print_double_stack(stack* a){
    printf("Top Stack:\n");
    int temp = a->top;
    while(a->top != -1)
        printf("%c", pop_odd(a));

    a->top = temp;
    temp = a->bottom;
    printf("\nBottom Stack:\n");
    while(a->bottom != 0)
        printf("%c", pop_even(a));

    a->bottom = temp;
}

void push_odd(stack* a, char data){
    if(a->top == MAX){
        printf("Error: Stack is full\n");
        return;
    }
    (a->top) += 2;
    a->data[a->top] = data;
}

char pop_odd(stack* a){
    if(a->top == -1){
        printf("Error: Stack is empty.\n");
        return ' ';
    }
    char data = a->data[a->top];
    (a->top)-=2;
    return data;
}

void push_even(stack* a, char data){
    if(a->bottom == MAX){
        printf("Error: Stack is full\n");
        return;
    }
    (a->bottom) += 2;
    a->data[a->bottom] = data;
}

char pop_even(stack* a){
    if(a->bottom == 0){
        printf("Error: Stack is empty.\n");
        return ' ';
    }
    char data = a->data[a->bottom];
    (a->bottom) -= 2;
    return data;
}


int main(){

    stack* a = init_stack();

    push_odd(a,'k');
    push_odd(a,'c');
    push_odd(a,'a');
    push_odd(a,'t');
    push_odd(a,'s');

    push_even(a,'k');
    push_even(a,'c');
    push_even(a,'a');
    push_even(a,'t');
    push_even(a,'s');

    print_double_stack(a);

    free_stack(a);
    return 0;
}
