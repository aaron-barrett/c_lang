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

int partition(node** head, int pivot){
    unsigned size = count_node(*head);
    int index = 0;
    node* temp = *head;
    for(int i = 0 ; i < size ; i++)
        if (temp->data >= pivot){
            node* hold = temp->neighbor;
            temp->neighbor = temp->neighbor->neighbor;
            hold->neighbor = temp;
            *head = hold;
            temp = push_right(hold);
        }
        else{
            index++;
            break;
        }
    if (index == 0)
        return index;
    temp = *head;
    for(int i = 0 ; i < size-1 ; i++)
        if (temp->neighbor->data >= pivot){
            temp = push_right(temp);
        }
        else{
            index++;
            temp = temp->neighbor;
        }
    return index;
}

node* quick_sort(node* head){

    unsigned size = count_node(head);

    if (size > 1){
        int index = partition(&head, head->data);
        node* left = head;
        node* right = NULL;

        for(int i = 0 ; i < index-1; i++)
            left = left->neighbor;

        right = left->neighbor;
        left->neighbor = NULL;

        left = quick_sort(head);
        right = quick_sort(right);

        head = left;

        while (left-> neighbor != NULL)
            left = left->neighbor;
        left->neighbor = right;
    }
    return head;
}

int main(){

    node* head = (node*)malloc(sizeof(node));
    head->data = -10;
    head->neighbor = NULL;
    create_node(head, 5);
    create_node(head, -2);
    create_node(head, 20);
    create_node(head, 1);
    create_node(head, 2);

    printf("Unsorted linked list: \n");
    print_list(head);

    head = quick_sort(head);
    if (sorted(head) == -1)
        printf("Fail: Linked List NOT Sorted.\n");
    else 
        printf("Success: Link List Sorted!\n");

    printf("Free linked list: \n");
    free_node(head);

    return 0;
}
