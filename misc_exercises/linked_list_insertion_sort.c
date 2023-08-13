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

node* place_left(node* head, int index){
    node* temp = head;
    for(int i = 0 ; i < index - 1; i++)
        temp = temp->neighbor;
    node* h = temp->neighbor;
    temp->neighbor = NULL;
    temp = h;
    node* end = temp->neighbor;
    temp->neighbor = NULL;

    node* hold = head;
    if(hold->data > temp->data){
        node* h = hold;
        hold = temp;
        hold->neighbor = h;
        head = hold;
    }

    for(int i = 0 ; i < index - 1 ; i++){
        if(hold->neighbor->data <= temp->data){
            if(hold->neighbor->neighbor == NULL){
                hold->neighbor->neighbor = temp;
                break;
            }
            else if (hold->neighbor->neighbor->data > temp->data){
                node* h= hold->neighbor->neighbor;
                hold->neighbor->neighbor = temp;
                temp->neighbor = h;
                break;
            }
            else 
                hold=hold->neighbor;
        }
        else{
            node* h = hold->neighbor;
            hold->neighbor = temp;
            temp->neighbor = h;
            break;
        }
    }

    hold = head;
    while(hold->neighbor != NULL)
        hold = hold->neighbor;
    hold->neighbor = end;
    return head;
}

node* insertion_sort(node* head){
    unsigned size = count_node(head);
    // Handles base case of comparing the first two elements
    if (head->data > head->neighbor->data){
        node* h = head->neighbor->neighbor;
        head->neighbor->neighbor = head;
        head->neighbor = h;
    }
    for(int i = 2 ; i < size ; i++)
        head = place_left(head, i);
    return head;
}

int main(){

    node* head = (node*)malloc(sizeof(node));
    head->data = -10;
    head->neighbor = NULL;
    create_node(head, 0);
    create_node(head, -6);
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
