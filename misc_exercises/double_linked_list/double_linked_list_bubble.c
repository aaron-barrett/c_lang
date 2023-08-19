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

node* bubble(node* head){

    int size = count_dll(head);
    node* temp;
    node* hold;
    for(int i = 0 ; i != size - 1 ; i++){
        temp = head;
        for(int j = 0 ; j != size - 1 - i ; j++)
            if(temp->data > temp->n->data){
                if(j == 0){
                    hold = temp->n->n;
                    temp->n->n = temp;
                    temp->n->p = NULL;
                    temp->p = temp->n;
                    temp->n = hold;
                    hold->p = temp;
                    head = temp->p;
                }
                else{
                    hold = temp->n->n;
                    temp->n->n = temp->n->p;
                    temp->n->p = temp->p;
                    temp->p->n = temp->n;
                    temp->p = temp->n;
                    temp->n = hold;
                    if(hold != NULL)
                        hold->p = temp;
                }
            }
            else 
                temp = temp->n;
    }
    
    return head;
}


int main(){

    node* head = add_node(NULL, -1);
    head = add_node(head, 8);
    head = add_node(head, 7);
    head = add_node(head, -10);

    printf("Double Linked List:\n");
    print_dll(head);

    head = bubble(head);
    int sort = sorted(head);
    if(sort == -1)
        printf("Double Linked List NOT Sorted.\n");
    else 
        printf("Double Linked List Sorted!\n");

    printf("Free Double Linked List:\n");
    free_dll(head);

    return 0 ;
}
