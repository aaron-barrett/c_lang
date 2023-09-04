#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct stack stack;
void push_top(stack*,char);
char pop_top(stack*);
void push_bottom(stack*,char);
char pop_bottom(stack*);
struct stack{
    char* data;
    int top;
    int bottom;
};

stack* init_stack(){
    stack* a = malloc(sizeof(stack));
    a->data = malloc(sizeof(char)*MAX);
    a->top = -1;
    a->bottom = MAX;
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
        printf("%c", pop_top(a));

    a->top = temp;
    temp = a->bottom;
    printf("\nBottom Stack:\n");
    while(a->bottom != MAX)
        printf("%c", pop_bottom(a));

    a->bottom = temp;
}

void push_top(stack* a, char data){
    if(a->top == MAX/2){
        printf("Error: Stack is full\n");
        return;
    }
    a->data[++(a->top)] = data;
}

char pop_top(stack* a){
    if(a->top == -1){
        printf("Error: Stack is empty.\n");
        return ' ';
    }
    char data = a->data[(a->top)--];
    return data;
}

void push_bottom(stack* a, char data){
    if(a->bottom == MAX/2){
        printf("Error: Stack is full\n");
        return;
    }
    a->data[--(a->bottom)] = data;
}

char pop_bottom(stack* a){
    if(a->bottom == MAX){
        printf("Error: Stack is empty.\n");
        return ' ';
    }
    char data = a->data[(a->bottom)++];
    return data;
}


int main(){

    stack* a = init_stack();

    push_top(a,'k');
    push_top(a,'c');
    push_top(a,'a');
    push_top(a,'t');
    push_top(a,'s');

    push_bottom(a,'k');
    push_bottom(a,'c');
    push_bottom(a,'a');
    push_bottom(a,'t');
    push_bottom(a,'s');

    print_double_stack(a);

    free_stack(a);
    return 0;
}
