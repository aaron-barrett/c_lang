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

node* inser_beginning(node* head, node* insert){
    insert->n = head;
    head->p = insert;
    head = insert;
    return head;
}

node* insert_prev(node* head, node* insert){
    if(head->p == NULL){
        head->p = insert;
        insert->n = head;
        head = insert;
    }
    else{
        node* hold = head->p;
        head->p = insert;
        insert->n = head;
        insert->p = hold;
        hold->n = insert;
    }
    return insert;
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

node* insert_end(node* head, node* insert){
    node* temp = head;
    while(temp->n != NULL)
        temp = temp->n;
    temp->n = insert;
    insert->p = temp;
    return head;
}

node* insert_middle(node* head, node* insert, int count){
    int size = count_dll(head);
    if (count == 0)
        head = insert_prev(head, insert);
    else if (count >= size)
        head = insert_end(head, insert);
    else{
        node* temp = head;
        for(int i = 0 ; i < count-1; i++)
            temp = temp->n;
        temp = insert_next(temp, insert);
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

    node* insert_n = add_node(NULL, -100);
    printf("Double Linked List Insert Next:\n");
    head = insert_next(head, insert_n);
    print_dll(head);

    node* insert_p = add_node(NULL, 100);
    printf("Double Linked List Insert Prev:\n");
    head->n = insert_prev(head->n, insert_p);
    print_dll(head);

    node* middle_insert = add_node(NULL, 10000);
    int insert_index = 0;
    head = insert_middle(head, middle_insert, insert_index);
    printf("Double Linked List Insert At Position %d:\n", insert_index);
    print_dll(head);

    free_dll(head);

    return 0 ;
}
