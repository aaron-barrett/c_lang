#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct stack stack;
void push(stack*,char);
char pop(stack*);

struct stack
{
    char* data;
    int top;
};

stack* init_stack()
{
    stack* a = malloc(sizeof(stack));
    a->data = malloc(sizeof(char)*MAX);
    a->top = -1;
    return a;
}

void free_stack(stack* a)
{
    free(a->data);
    free(a);
}

void print_stack(stack* a)
{
    int top = a->top;
    while(top != -1)
        printf("%c", a->data[top--]);
    printf("\n");
}

void push(stack* a, char data)
{
    if(a->top == MAX-1)
    {
        printf("Error: Stack is full\n");
        return;
    }
    a->data[++(a->top)] = data;
}

char pop(stack* a)
{
    if(a->top == -1)
    {
        printf("Error: Stack is empty.\n");
        return ' ';
    }
    char data = a->data[(a->top)--];
    return data;
}

void parenthesis_permutations(stack* s, int pairs, int pair_count, int ham, int* total_perms)
{
    if (pair_count == pairs && ham == 0)
    {
        print_stack(s);
        (*total_perms)++;
        return;
    }
    if (pairs + ham > 0)
    {
        push(s, ')');
        parenthesis_permutations(s, pairs, pair_count, ham-1, total_perms);
        pop(s);
    }
    if (ham < 0 && pair_count != pairs)
    {
        push(s, '(');
        parenthesis_permutations(s, pairs, pair_count+1, ham+1, total_perms);
        pop(s);
    }
}


int main()
{
    stack* s = init_stack();
    int dim = 3; 
    int count = 0;
    int ham = 0;
    int total = 0;
    parenthesis_permutations(s, dim, count, ham, &total);
    // catalan number for n = dim
    printf("Total permutations: %d\n", total);
    free_stack(s);
    return 0;
}
