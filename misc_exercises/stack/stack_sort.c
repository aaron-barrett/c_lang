#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct stack stack;
void push(stack*,int);
int pop(stack*);

struct stack{
    int* data;
    int top;
};

stack* init_stack(){
    stack* a = malloc(sizeof(stack));
    a->data = malloc(sizeof(int)*MAX);
    a->top = -1;
    return a;
}

void free_stack(stack* a){
    free(a->data);
    free(a);
}

void print_stack(stack* a){
    if (a->top == -1)
        return ;
    int hold = pop(a);
    print_stack(a);
    printf("%d ", hold);
    push(a, hold);
}

void push(stack* a, int data){
    if(a->top == MAX-1){
        printf("Error: Stack is full\n");
        return;
    }
    a->data[++(a->top)] = data;
}

int pop(stack* a){
    if(a->top == -1){
        printf("Error: Stack is empty.\n");
        return ' ';
    }
    int data = a->data[(a->top)--];
    return data;
}

void sort_stack(stack** a){
    stack* sort = init_stack();
    int temp;
    while((*a)->top != -1){
        temp = pop(*a);
        while(sort->top != -1 && sort->data[sort->top] > temp)
            push(*a, pop(sort));
        push(sort, temp);
    }
    free(*a);
    *a = sort;
}


int main(){

    stack* a = init_stack();
    push(a, 100);
    push(a, 2);
    push(a, -1);
    push(a, 3);
    push(a, -2);

    printf("Unsorted Stack:\n");
    print_stack(a);
    printf("\n");
    sort_stack(&a);
    printf("Sorted stack:\n");
    print_stack(a);

    free_stack(a);
    return 0;
}
