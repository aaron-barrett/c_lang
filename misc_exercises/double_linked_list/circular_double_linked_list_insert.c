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
        node* head = (node*)(malloc(sizeof(node)));
        head->data = data;
        head->n = head;
        head->p = head;
        return head;
    }
    node* read = head;
    while(read->n != head)
        read = read->n;
    read->n = (node*)(malloc(sizeof(node)));
    read->n->p = read;
    read = read->n;
    read->data = data;
    read->n = head;
    head->p = read;
    return head;    
}

node* create_dll_circular(int count, int inc){
    if (count == 0)
        return NULL;
    node* head = (node*)(malloc(sizeof(node)));
    head->data = 0;
    head->n = NULL;
    head->p = NULL;

    node* temp = head;
    for(int i = 1 ; i < count; i++){
        temp->n = (node*)(malloc(sizeof(node)));
        temp->n->p = temp;
        temp = temp->n;
        temp->data = i * inc;
        temp->n = NULL;
    }
    head->p = temp;
    temp->n = head;
    return head;
}

void free_dll_circular(node* head){
    node* del = head;
    do{
        node* temp = del->n;
        free(del);
        del = temp;
    } while(del != head);
}

int count_dll_circular(node* head){
    int size = 0 ;
    node* read = head;
    do{
        read = read->n;
        size++;
    } while(read != head);
    return size;
}

void print_dll_circular(node* head){
    node* read = head;
    do{
        printf("node->data: %d\n", read->data);
        read = read->n;
    } while(read != head);
    printf("(show circular) node->data: %d\n", read->data);
}

void print_dll_circular_reverse(node* head){
    node* read = head;
    do{
        printf("node->data: %d\n", read->data);
        read = read->p;
    } while(read != head);
    printf("(show circular) node->data: %d\n", read->data);

}

node* insert_prev(node* head, node* insert){
    if (head == NULL)
        return insert;
    node* hold = head->p;
    head->p = insert;
    insert->n = head;
    insert->p = hold;
    hold->n = insert;
    return head;
}

node* insert_next(node* head, node* insert){
    if (head == NULL)
        return insert;
    node* hold = head->n;
    head->n = insert;
    insert->p = head;
    insert->n = hold;
    hold->p = insert;
    return head;
}

node* insert_mid(node* head, node* insert, int index){
    int size = count_dll_circular(head);
    if (size == 0)
        return insert;
    if (index >= size)
        head = insert_prev(head, insert);
    else if (index == 0){
        head = insert_prev(head, insert);
        head = head->p;
    }
    else {
        node* temp = head;
        for(int i = 0 ; i < index -1; i++)
            temp = temp->n;
        temp = insert_next(temp, insert);
    }
    return head;
}

int main(){

    node* head = add_node(NULL, 1);
    head = add_node(head, 2);
    head = add_node(head, 3);
    head = add_node(head, 4);
    printf("Circular Double Linked List:\n");
    print_dll_circular(head);

    node* insert_p = add_node(NULL, 5);
    head = insert_prev(head, insert_p);
    printf("Circular Double Linked List Insert Prev:\n");
    print_dll_circular(head);


    node* insert_n = add_node(NULL, 2);
    head = insert_next(head, insert_n);
    printf("Circular Double Linked List Insert Next:\n");
    print_dll_circular(head);

    node* insert_m = add_node(NULL, 0);
    int index = 0;
    head = insert_mid(head, insert_m, index);
    printf("Circular Double Linked List Insert Middle at %d:\n", index);
    print_dll_circular(head);

    printf("Circular Double Linked List Print Reverse %d:\n", index);
    print_dll_circular_reverse(head);


    free_dll_circular(head);

    return 0 ;
}
