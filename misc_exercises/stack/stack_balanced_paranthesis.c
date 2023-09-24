#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

char stack[MAX];
int top = -1;

void push(char data){
    if(top == MAX-1){
        printf("Error: Stack is full\n");
        return;
    }
    stack[++top] = data;
}

char pop(){
    if(top == -1){
        printf("Error: Stack is empty.\n");
        return ' ';
    }
    char data = stack[top--];
    return data;
}

int is_matching_pair(char a, char b){
    if (a == '(' && b == ')')
        return 0;
    if (a == '[' && b == ']')
        return 0;
    if (a == '{' && b == '}')
        return 0;
    return -1;
}

int is_balanced(char* text){

    for(int i = 0 ; i < strlen(text); i++)
        if (text[i] == '(' || text[i] == '[' || text[i] == '{')
            push(text[i]);
        else if (text[i] == ')' || text[i] == ']' || text[i] == '}')
            if (top == -1 || is_matching_pair(pop(), text[i]) == -1)
                return -1;
                
    return top == -1 ? 1 : -1;
}


int main(){

    char* text = "([]){}[[(){}]{}]";
    // char* text = "([]){}[[(){}]{]";
    // char* text = "([]){]";

    if(is_balanced(text) == 1)
        printf("Parenthesis are Balanced.\n");
    else 
        printf("Parenthesis are NOT Balanced.\n");
    printf("%s\n", text);
    return 0;
}
