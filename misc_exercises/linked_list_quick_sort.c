#include <stdio.h>
#include <stdlib.h>

typedef struct node node; 
struct node{
    int data;
    node* neighbor;
};

void  create_node(node* head, int data){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->neighbor = NULL;
    while(head->neighbor != NULL)
        head = head->neighbor;
    head->neighbor = new_node;
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
        printf("delte node ->data: %d\n", head->data);
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

node* push_right(node* head){
    node* temp = head;
    while (temp->neighbor->neighbor!= NULL){
        node* hold = temp->neighbor->neighbor->neighbor;
        temp->neighbor->neighbor->neighbor = temp->neighbor;
        temp->neighbor = temp->neighbor->neighbor;
        temp->neighbor->neighbor->neighbor = hold;
        temp = temp->neighbor;
    }
    return head;
}

unsigned partition(node** head, int pivot){
    unsigned size = count_node(*head);
    unsigned index = 0;
    node* temp = *head;
    for(int i = 0 ; i < size-1 ; i++ ){
        if (temp->data > pivot){
            node* hold = temp->neighbor;
            temp->neighbor = temp->neighbor->neighbor;
            hold->neighbor = temp;
            *head = hold;
            temp = hold;
            temp = push_right(temp);
        }
        else if (temp->neighbor->data > pivot){
            temp = push_right(temp);
        }
        else {
            index++;
            temp = temp->neighbor;
        }
    }
    return index;
}


node* quick_sort(node* head){
    unsigned size = count_node(head);
    if (size > 1){
        unsigned index = partition(&head, head->data);
        node* mid = NULL ;
        node* it = head;
        node* hold2 = NULL;
        for(int i = 0 ; i < index; i++)
            it = it->neighbor;

        mid = it->neighbor;
        if (it->neighbor != NULL)
            hold2 = it->neighbor->neighbor;

        it->neighbor = NULL;

        head = quick_sort(head);
        hold2 = quick_sort(hold2);
        
        it = head;
        while(it->neighbor != NULL)
            it = it->neighbor;
        it->neighbor= mid;
        mid->neighbor = hold2;
    }
    return head;
}

int main(){

    node* head = (node*)malloc(sizeof(node));
    head->data = -1;
    head->neighbor = NULL;
    create_node(head, 5);
    create_node(head, 5);
    create_node(head, 1);
    create_node(head, 2);
    create_node(head, 3);

    printf("Unsorted linked list: \n");
    print_list(head);


    // unsigned index = partition(&head, head->data);
    // printf("Linked List partitioned around element in index %d.\n", index);
    // print_list(head);

    head = quick_sort(head);
    printf("Sorted linked list: \n");
    print_list(head);

    printf("Free linked list: \n");
    free_node(head);

    return 0;
}
