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

node* bubble_sort(node* head){
    unsigned size = count_node(head);
    unsigned stop = 1 ; 
    node* prev;
    node* hold;
    for (unsigned i = 0 ; i < size - 1 ; i++){
        prev = head;
        hold = head->neighbor;
        stop = 1;
        for(unsigned j = 0 ; j < size - 1 - i  ; j++){
            if (j == 0){
                if (prev->data >= hold->data){
                    prev->neighbor = hold->neighbor;
                    hold->neighbor = prev;
                    prev = hold;
                    hold = hold->neighbor;
                    head = prev;
                    stop = 0;
                }
            }
            else{
                if (hold->data >= hold->neighbor->data){
                    node* h = hold->neighbor->neighbor;
                    prev->neighbor = hold->neighbor;
                    prev->neighbor->neighbor = hold;
                    prev->neighbor->neighbor->neighbor = h;
                    prev = prev->neighbor;
                    stop = 0;
                }
                else{
                    prev = prev->neighbor;
                    hold = hold->neighbor;
                }
            }
        }
        if (stop == 1)
            return head;
    }
    return head;
}

int main(){

    node* head = (node*)malloc(sizeof(node));
    head->data = 5;

    node* h1 = (node*)malloc(sizeof(node));
    h1->data = -1;

    node* h2 = (node*)malloc(sizeof(node));
    h2->data = 1;

    node* h3 = (node*)malloc(sizeof(node));
    h3->data = 2;

    node* h4 = (node*)malloc(sizeof(node));
    h4->data = -5;

    head->neighbor = h1;
    h1->neighbor = h2;
    h2->neighbor = h3;
    h3->neighbor = h4;
    h4->neighbor = NULL;

    printf("Unsorted linked list: \n");
    print_list(head);

    head = bubble_sort(head);

    printf("Sorted linked list: \n");
    print_list(head);

    printf("Free linked list: \n");
    free_node(head);

    return 0;
}
