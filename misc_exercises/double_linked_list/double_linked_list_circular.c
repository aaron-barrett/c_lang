#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
    int data ; 
    node* p;
    node* n;
};

int count_dll_circular(node* head){
    int size = 0 ;
    node* read = head;
    while(read->n != head){
        read = read->n;
        size++;
    }
    return size;
}

void free_dll_circular(node* head){
    node* del = head;
    while(del->n != head){
        printf("free node->data: %d\n", del->data);
        node* temp = del->n;
        free(del);
        del = temp;
    }
}

void print_dll_circular(node* head){
    node* read = head;
    while(read->n != head){
        printf("node->data: %d\n", read->data);
        read = read->n;
    }
}

node* create_dll_circular(int count, int inc){
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
    head->p = temp;
    temp->n = head;
    return head;
}

int main(){

    node* head = create_dll_circular(5, 10);
    printf("Circular Linked List:\n");
    print_dll_circular(head);

    printf("Circular DLL has size %d\n", count_dll_circular(head));

    free_dll_circular(head);

    return 0 ;
}
