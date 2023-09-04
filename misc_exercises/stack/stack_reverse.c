#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct stack stack;
void push(stack*,char);
char pop(stack*);

struct stack{
    char* data;
    int top;
};

stack* init_stack(){
    stack* a = malloc(sizeof(stack));
    a->data = malloc(sizeof(char)*MAX);
    a->top = -1;
    return a;
}

void free_stack(stack* a){
    free(a->data);
    free(a);
}

void print_stack(stack* a){
   while(a->top != -1)
        printf("%c", pop(a));
}

void push(stack* a, char data){
    if(a->top == MAX-1){
        printf("Error: Stack is full\n");
        return;
    }
    a->data[++(a->top)] = data;
}

char pop(stack* a){
    if(a->top == -1){
        printf("Error: Stack is empty.\n");
        return ' ';
    }
    char data = a->data[(a->top)--];
    return data;
}

stack* reverse(stack* a){
    stack* reverse = init_stack();
    while(a->top != -1)
        push(reverse, pop(a));
    return reverse;
}

int main(){

    stack* a = init_stack();
    push(a,'k');
    push(a,'c');
    push(a,'a');
    push(a,'t');
    push(a,'s');

    printf("Reverse:\n");
    stack* r = reverse(a);
    print_stack(r);

    free_stack(a);
    free_stack(r);
    return 0;
}
