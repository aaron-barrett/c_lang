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

int sorted(node* head){
    int size = count_dll(head);
    for(int i = 0 ; i < size ; i++)
        if(head->data > head->n->data)
            return -1 ; 
    return 0;
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
            temp->p = hold;
            hold->n = temp;
        }
        else{
            temp = temp->n;
            index++;
        }
    return index;
}

node* quick_sort(node* head){

    unsigned size = count_dll(head);
    
    if (size > 1){
        int index = partition(&head, head->data);
        node* left = head;
        node* right = NULL;

        for(int i = 0 ; i < index-1; i++)
            left = left->n;

        right = left->n;
        right->p = NULL;
        left->n = NULL;

        left = quick_sort(head);
        right = quick_sort(right);

        head = left;

        while (left->n != NULL)
            left = left->n;
        left->n = right;
        right->p = left;
    }
    return head;
}


int main(){

    node* head = add_node(NULL, 0);
    head = add_node(head, 5);
    head = add_node(head, -1);
    head = add_node(head, 10);

    printf("Double Linked List:\n");
    print_dll(head);

    head = quick_sort(head);
    int sort = sorted(head);
    if(sort == -1)
        printf("Double Linked List NOT Sorted.\n");
    else 
        printf("Double Linked List Sorted!\n");

    printf("Free Double Linked List:\n");
    free_dll(head);

    return 0 ;
}
