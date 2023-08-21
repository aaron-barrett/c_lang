#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node {
    int data ; 
    node* p;
    node* n;
};

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

void free_dll(node* head){
    while(head != NULL){
        node* temp = head->n;
        free(head);
        head = temp;
    }
}

void print_dll(node* head){
    while(head != NULL){
        printf("node->data: %d\n", head->data);
        head = head->n;
    }
}

node* reverse(node* head){
    while(head->n != NULL){
        node* temp = head->n;
        head->n = head->p;
        head->p = temp;
        head = temp;
    }
    head->n = head->p;
    head->p = NULL;
    return head;    
}

node* create_dll(int count, int inc){
    if (count == 0)
        return NULL;
    node* head = (node*)(malloc(sizeof(node)));
    head->data = 0;
    head->n = NULL;
    head->p = NULL;

    node* temp = head;
    for(int i = 1 ; i < count+1; i++){
        temp->n = (node*)(malloc(sizeof(node)));
        node* hold = temp;
        temp = temp->n;
        temp->data = i * inc;
        temp->n = NULL;
        temp->p = hold;
    }
    return head;
}

node* insert_next(node* head, node* insert){
    if(head == NULL)
        return insert;
    node* temp = head->n;
    head->n = insert;
    insert->n = temp;
    insert->p = head;
    if(temp != NULL)
        temp->p = insert;
    return head;
}

node* remove_next(node* head){
    if (head == NULL)
        return head;
    node* remove = head->n;
    if (remove == NULL)
        return head;
    else if (remove->n != NULL){
        head->n = remove->n;
        head->n->p = head;
    }
    else
        head->n = NULL;
    remove->p = NULL;
    remove->n = NULL;
    return remove;
}


int main(){

    node* head = add_node(NULL, -1);
    head = add_node(head, 8);
    head = add_node(head, 7);
    head = add_node(head, -10);

    node* insert = add_node(NULL, -100);

    printf("Double Linked List:\n");
    print_dll(head);
    printf("Insert Node:\n");
    print_dll(insert);

    printf("Double Linked List Insert:\n");
    head = insert_next(head, insert);
    print_dll(head);
    
    insert = remove_next(head);
    printf("Double Linked List Remove:\n");
    print_dll(head);
    printf("Removed Node:\n");
    print_dll(insert);

    free_dll(head);

    return 0 ;
}
