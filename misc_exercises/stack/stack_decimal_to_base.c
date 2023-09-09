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

void print_base(stack* a){
   while(a->top != -1)
        printf("%i", pop(a));
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

stack* dec_to_bin(int dec, int base){
    stack* bin = init_stack();
    while(dec > 0){
        push(bin, dec % base);
        dec /= base;
    }
    return bin;
}

int main(){
    int dec = 10;
	int base = 3;
    stack* a = dec_to_bin(dec, base);
    printf("%d in base %d:\n", dec, base);
    print_base(a);
    free_stack(a);
    return 0;
}
