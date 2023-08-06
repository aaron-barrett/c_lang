#include <stdio.h>
#include <stdlib.h>

typedef struct node node; 
struct node{
    int data;
    node* neighbor;
};

node* create_linked_list(unsigned size){
    node* head = (node*)malloc(sizeof(node));
    node* temp = head;
    for(int i = 0 ; i < size ; i++){
        head->data = i;
        if (i != size - 1){
            head->neighbor = (node*)malloc(sizeof(node));
            head = head->neighbor;
        }
        else 
            head->neighbor = NULL;
    }
    return temp;
}

void print_list(node* head){
    while(head != NULL){
        printf("node -> data %d \n", head->data);
        head = head->neighbor;
    }
}

void free_node(node* head){
    node* temp;
    while(head != NULL){
        printf("delete node ->data: %d\n", head->data);
        temp = head->neighbor;
        free(head);
        head = temp;
    }
}

unsigned count_node(node* head){
    unsigned count = 0 ; 
    while(head != NULL){
        count++;
        head = head->neighbor;
    }
    return count;
}

void swap_consecutive_nodes(node**head, unsigned i1){
    node* temp1 = *head;
    node* temp2 = (*head)->neighbor;
    if (i1 == 0){
        node* hold = temp2->neighbor;
        temp2->neighbor = temp1;
        temp1->neighbor = hold;
        *head = temp2;
        return ;
    }
    unsigned size = count_node(*head);
    for(unsigned i = 1 ; i < size - 1; i++){
        if (i == i1){
            node* hold = temp2->neighbor->neighbor;
            temp1->neighbor = temp2->neighbor;
            temp1->neighbor->neighbor = temp2;
            temp1->neighbor->neighbor->neighbor = hold;
            return ;
        }
        temp1 = temp1->neighbor;
        temp2 = temp2->neighbor;
    }
}

int main(){

    node* head = (node*)malloc(sizeof(node));
    head->data = -1;

    node* h1 = (node*)malloc(sizeof(node));
    h1->data = 5;

    node* h2 = (node*)malloc(sizeof(node));
    h2->data = 1;

    node* h3 = (node*)malloc(sizeof(node));
    h3->data = 2;

    node* h4 = (node*)malloc(sizeof(node));
    h4->data = 3;

    head->neighbor = h1;
    h1->neighbor = h2;
    h2->neighbor = h3;
    h3->neighbor = h4;
    h4->neighbor = NULL;

    printf("Linked list: \n");
    print_list(head);

    unsigned index = 0 ; 

    swap_consecutive_nodes(&head, index);

    printf("After Swapping %d and %d: \n", index, index+1);
    print_list(head);

    printf("Free linked list: \n");
    free_node(head);

    return 0;
}
