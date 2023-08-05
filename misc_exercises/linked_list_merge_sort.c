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

node* merge(node* n1, node* n2){
    node* merge = (node*)malloc(sizeof(node));
    node* temp = merge;
    node* del_temp;
    unsigned size  = count_node(n1) + count_node(n2);
    for(int i = 0 ; i < size; i++){
        if (n1 == NULL){
            merge->data = n2->data;
            del_temp = n2;
            n2 = n2->neighbor;
        }
        else if (n2 == NULL){
            merge->data = n1->data;
            del_temp = n1;
            n1 = n1->neighbor;
        }
        else
            if (n1->data <= n2->data){
                merge->data = n1->data;
                del_temp = n1;
                n1 = n1->neighbor;
            }
            else{
                merge->data = n2->data;
                del_temp = n2;
                n2 = n2->neighbor;
            }
        free(del_temp);
        if (i == size-1)
            merge->neighbor = NULL;
        else{
            merge->neighbor = (node*)malloc(sizeof(node));
            merge = merge->neighbor;
        }
    }
    return temp;
}

node* merge_sort(node* head){
    unsigned size = count_node(head);
    if (size > 1){
        node* hold = head->neighbor;
        node* hold2 = head;
        for(unsigned i = 0 ; i < (size/2)-1; i++){
            hold = hold->neighbor;
            hold2 = hold2->neighbor;
        }
        hold2->neighbor = NULL;
        head = merge_sort(head);
        hold = merge_sort(hold);
        head = merge(head, hold);
    }
    return head;
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

    printf("Unsorted linked list: \n");
    print_list(head);

    head = merge_sort(head);

    printf("Sorted linked list: \n");
    print_list(head);

    printf("Free linked list: \n");
    free_node(head);

    return 0;
}
