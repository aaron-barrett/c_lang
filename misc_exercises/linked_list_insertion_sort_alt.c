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

int sorted(node*head){
    while(head->neighbor != NULL){
        if (head->neighbor->data < head->data)
            return -1;
        head = head->neighbor;
    }
    return 1;
}

node* insert_node(node* merged, node* insert){
    insert->neighbor = NULL;
    if (merged == NULL)
        merged = insert;
    else{
        node* temp = merged;
        while(temp->neighbor != NULL && temp->neighbor->data <= insert->data)
            temp = temp->neighbor;
        if (temp->neighbor == NULL){
            if (temp->data <= insert->data){
                temp->neighbor = insert;
            }
            else{
                node* hold = merged;
                merged = insert;
                insert->neighbor = hold;
            }
        }
        else{
            node* hold = temp->neighbor;
            temp->neighbor = insert;
            insert->neighbor = hold;
        }
    }
    return merged;
}

node* insertion_sort(node* head){
    node* merged = NULL;
    while (head != NULL){
        printf("here\n");
        node* insert = head;
        head = head->neighbor;
        merged = insert_node(merged, insert);
        print_list(merged);

    }
    return merged;
}

int main(){

    node* head = (node*)malloc(sizeof(node));
    head->data = -10;
    head->neighbor = NULL;
    create_node(head, -20);
    create_node(head, -15);
    create_node(head, 0);
    create_node(head, -2);
    create_node(head, -9);

    printf("Unsorted linked list: \n");
    print_list(head);

    head = insertion_sort(head);
    if (sorted(head) == -1)
        printf("Fail: Linked List NOT Sorted.\n");
    else 
        printf("Success: Link List Sorted!\n");

    printf("Free linked list: \n");
    free_node(head);

    return 0;
}
