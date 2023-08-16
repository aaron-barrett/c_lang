#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
    int data ; 
    node* p;
    node* n;
};

void free_dll(node* head){
    while(head != NULL){
        printf("node->data free %d\n", head->data);
        node*temp = head->n;
        free(head);
        head = temp;
    }
}

void print_dll(node* head){
    while(head != NULL){
        printf("node->data: %d\n", head->data);
        head = head->n;
    }
}

node* reverse(node* head){
    while(head->n != NULL){
        node* temp = head->n;
        head->n = head->p;
        head->p = temp;
        head = temp;
    }
    head->n = head->p;
    head->p = NULL;
    return head;    
}

node* create_dll(int count, int inc){
    if (count == 0)
        return NULL;
    node* head = (node*)(malloc(sizeof(node)));
    head->data = 0;
    head->n = NULL;
    head->p = NULL;

    node* temp = head;
    for(int i = 1 ; i < count+1; i++){
        temp->n = (node*)(malloc(sizeof(node)));
        node* hold = temp;
        temp = temp->n;
        temp->data = i * inc;
        temp->n = NULL;
        temp->p = hold;
    }
    return head;
}


int main(){

    node* head = create_dll(4, 2);

    printf("Double Linked List:\n");
    print_dll(head);

    printf("Double Linked List Reverse:\n");
    head = reverse(head);
    print_dll(head);
    
    printf("Free Double Linked List:\n");
    free_dll(head);

    return 0 ;
}
