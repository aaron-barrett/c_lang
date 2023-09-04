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
    int top_hold = a->top;
   while(a->top != -1)
        printf("%c", pop(a));
    a->top = top_hold;
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

char remove_middle(stack** a, int k){
    stack* hold = init_stack();
    int count = (*a)->top - k;
    for(int i = 0 ; i < count; i++)
        push(hold, pop(*a));
    
    char mid = pop(*a);

    while(hold->top != -1)
        push(*a,pop(hold));

    free(hold);
    return mid;
}


int main(){

    stack* a = init_stack();

    push(a,'k');
    push(a,'c');
    push(a,'a');
    push(a,'t');
    push(a,'s');

    printf("Before removing mid:\n");
    print_stack(a);

    int mid = 0;
    char m = remove_middle(&a, mid);

    printf("\nRmoved %dth element '%c':\n", mid, m);
    print_stack(a);

    free_stack(a);
    return 0;
}
