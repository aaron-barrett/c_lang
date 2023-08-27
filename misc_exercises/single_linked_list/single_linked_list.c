#include <stdio.h>
#include <stdlib.h>

typedef struct node node; 
struct node{
    int data;
    node* n;
};

node* add_node(node* head, int data){
    if (head == NULL){
        head = (node*)(malloc(sizeof(node)));
        head->n = NULL;
        head->data = data;
        return head;
    }
    node* temp = head;
    while(temp->n != NULL)
        temp = temp->n;
    temp->n = (node*)malloc(sizeof(node));
    temp = temp->n;
    temp->data = data;
    temp->n = NULL;
    return head;
}

node* create_linked_list(unsigned size, int inc){
    node* head = (node*)malloc(sizeof(node));
    head->n = NULL;
    head->data = 0;
    node* temp = head;
    for(int i = 1 ; i < size; i++){
        temp->n = (node*)malloc(sizeof(node));
        temp = temp->n;
        temp->data = i*inc;
    }
    temp->n = NULL;
    return head;
}

void print_list(node* head){
    while(head != NULL){
        printf("node -> data %d \n", head->data);
        head = head->n;
    }
}

void free_node(node* head){
    node* temp;
    while(head != NULL){
        temp = head->n;
        free(head);
        head = temp;
    }
}

unsigned count_node(node* head){
    unsigned count = 0 ; 
    while(head != NULL){
        count++;
        head = head->n;
    }
    return count;
}

node* reverse(node* head){
    node* current = head;
    node* prev = NULL;
    node* next = NULL;
    while(current != NULL){
        next = current->n;
        current->n = prev;
        prev = current;
        current = next;
    }
    return prev;
}

int main(){

    node* head = create_linked_list(5,10);

    printf("Linked List: \n");
    print_list(head);

    head = reverse(head);
    printf("Reversed Linked List: \n");
    print_list(head);

    printf("Free linked list: \n");
    free_node(head);

    return 0;
}
