#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
    int data ; 
    node* p;
    node* n;
};

node* create_dll_circular(int count, int inc){
    if (count == 0)
        return NULL;
    node* head = (node*)(malloc(sizeof(node)));
    head->data = 0;
    head->n = NULL;
    head->p = NULL;

    node* temp = head;
    for(int i = 1 ; i < count; i++){
        temp->n = (node*)(malloc(sizeof(node)));
        temp->n->p = temp;
        temp = temp->n;
        temp->data = i * inc;
        temp->n = NULL;
    }
    head->p = temp;
    temp->n = head;
    return head;
}

void free_dll_circular(node* head){
    node* del = head;
    do{
        node* temp = del->n;
        free(del);
        del = temp;
    } while(del != head);
}

int count_dll_circular(node* head){
    int size = 0 ;
    node* read = head;
    do{
        read = read->n;
        size++;
    } while(read != head);
    return size;
}

void print_dll_circular(node* head){
    node* read = head;
    do{
        printf("node->data: %d\n", read->data);
        read = read->n;
    } while(read != head);
}

void print_dll_circular_reverse(node* head){
    node* read = head;
    do{
        printf("node->data: %d\n", read->data);
        read = read->p;
    } while(read != head);
}

int main(){

    node* head = create_dll_circular(5, 10);
    printf("Circular Double Linked List:\n");
    print_dll_circular(head);

    printf("Circular DLL has size %d\n", count_dll_circular(head));

    printf("Circular Double Linked List Reverse:\n");
    print_dll_circular_reverse(head);

    free_dll_circular(head);

    return 0 ;
}
