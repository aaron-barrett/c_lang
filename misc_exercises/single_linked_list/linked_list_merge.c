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
    unsigned count = 0; 
    while(head != NULL){
        count++;
        head = head->neighbor;
    }
    return count;
}

node* merge(node* n1, node* n2){
    node* merge = (node*)malloc(sizeof(node));
    node* temp = merge;
    int count1 = count_node(n1);
    int count2 = count_node(n2);
    node* del_temp;
    for(int i = 0 ; i < count1+count2; i++){
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
        if (i == count1+count2-1)
            merge->neighbor = NULL;
        else{
            merge->neighbor = (node*)malloc(sizeof(node));
            merge = merge->neighbor;
        }
    }
    return temp;
}

int main(){

    node* head = create_linked_list(4);
    node* h = create_linked_list(3);

    printf("List 1: \n");
    print_list(head);

    printf("List 2: \n");
    print_list(h);

    node* sorted = merge(head, h);

    printf("Sorted linked list: \n");
    print_list(sorted);

    printf("Free linked list: \n");
    free_node(sorted);

    return 0;
}
