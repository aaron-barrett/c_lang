#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
    int data ; 
    node* p;
    node* n;
};

int count_dll(node* head){
    int size = 0 ; 
    while(head != NULL){
        head = head->n;
        size++;
    }
    return size;
}

void free_dll(node* head){
    while(head != NULL){
        printf("node->data free %d\n", head->data);
        node*temp = head->n;
        free(head);
        head = temp;
    }
}

node* add_node(node* head, int data){
    if (head == NULL){
        head = (node*)(malloc(sizeof(node)));
        head->n = NULL;
        head->p = NULL;
        head->data = data;
        return head;
    }
    node* temp = head;
    while(temp->n != NULL)
        temp = temp->n;
    temp->n = (node*)(malloc(sizeof(node)));
    temp->n->p = temp;
    temp = temp->n;
    temp->data = data;
    temp->n = NULL;
    return head;
}

void print_dll(node* head){
    while(head != NULL){
        printf("node->data: %d\n", head->data);
        head = head->n;
    }
}

node* push_right(node* head){
    if (head->n == NULL)
        return head;
    node* temp = head;
    head = head->n;
    head->p = NULL;
    while(head->n != NULL)
        head = head->n;
    head->n = temp;
    temp->p = head;
    temp->n = NULL;
    while(head->p != NULL)
        head = head->p;
    return head;
}

int partition(node** head, int pivot){

    int index = 0 ;
    int size = count_dll(*head);
    node* temp = *head;

    for(int i = 0 ; i < size ; i++)
        if(temp->data >= pivot)
            temp = push_right(temp);
        else
            break;

    *head = temp;

    for(int i = 0 ; i < size-1; i++)
        if(temp->data > pivot){
            node* hold = temp->p;
            temp->p = NULL;
            temp = push_right(temp);
            print_dll(temp);
            temp->p = hold;
            hold->n = temp;
        }
        else{
            temp = temp->n;
            index++;
        }
    return index;
}


int main(){

    node* head = add_node(NULL, 10);
    head = add_node(head, 5);
    head = add_node(head, -1);
    head = add_node(head, 10);

    printf("Double Linked List:\n");
    print_dll(head);

    int pivot = head->data;
    int index = partition(&head, pivot);
    printf("Double Linked List Partitioned with %d at index %d.\n", pivot, index);
    print_dll(head);

    printf("Free Double Linked List:\n");
    free_dll(head);

    return 0 ;
}
