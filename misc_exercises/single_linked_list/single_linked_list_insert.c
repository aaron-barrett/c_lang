#include <stdio.h>
#include <stdlib.h>

typedef struct node node; 
struct node{
    int data;
    node* n;
};

node* add_node(node* head, int data){
    if (head == NULL){
        head = (node*)(malloc(sizeof(node)));
        head->n = NULL;
        head->data = data;
        return head;
    }
    node* temp = head;
    while(temp->n != NULL)
        temp = temp->n;
    temp->n = (node*)malloc(sizeof(node));
    temp = temp->n;
    temp->data = data;
    temp->n = NULL;
    return head;
}

node* create_linked_list(unsigned size, int inc){
    node* head = (node*)malloc(sizeof(node));
    head->n = NULL;
    head->data = 0;
    node* temp = head;
    for(int i = 1 ; i < size; i++){
        temp->n = (node*)malloc(sizeof(node));
        temp = temp->n;
        temp->data = i*inc;
    }
    temp->n = NULL;
    return head;
}

void print_list(node* head){
    while(head != NULL){
        printf("node -> data %d \n", head->data);
        head = head->n;
    }
}

void free_node(node* head){
    node* temp;
    while(head != NULL){
        temp = head->n;
        free(head);
        head = temp;
    }
}

unsigned count_node(node* head){
    unsigned count = 0 ; 
    while(head != NULL){
        count++;
        head = head->n;
    }
    return count;
}

node* reverse(node* head){
    node* current = head;
    node* prev = NULL;
    node* next = NULL;
    while(current != NULL){
        next = current->n;
        current->n = prev;
        prev = current;
        current = next;
    }
    return prev;
}


node* insert_head(node* head, node* insert){
    insert->n = head;
    return insert;
}

node* insert_prev(node* head, node* current, node* insert){
    if(head == current)
        head = insert_head(head, insert);
    node* temp = head;
    while(temp->n != current)
        temp = temp->n;
    node* hold = temp->n;
    temp->n = insert;
    insert->n = hold;
    return head;
}

node* insert_next(node* head, node* insert){
    node* next = head->n;
    head->n = insert;
    insert->n = next;
    return head;
}

node* insert_end(node* head, node* insert){
    if(head == NULL)
        return insert;
    node* temp = head;
    while(temp->n != NULL)
        temp = temp->n;
    temp->n = insert;
    return head;
}

node* insert_middle(node* head, node* insert, int index){
    if (head == NULL)
        return insert;
    int size = count_node(head);
    if (index == 0)
        head = insert_head(head, insert);
    else if (index >= size)
        head = insert_end(head, insert);
    else {
        node* temp = head;
        for(int i = 0 ; i < index-1 ; i++)
            temp = temp->n;
        temp = insert_next(temp, insert);
    }
    return head;
}


int main(){

    node* head = create_linked_list(5,10);
    printf("Linked List: \n");
    print_list(head);

    node* insert_h = add_node(NULL, 100);
    head = insert_head(head, insert_h);
    printf("Linked List Insert Head:\n");
    print_list(head);

    node* insert_p = add_node(NULL, -500);
    head = insert_prev(head, head->n, insert_p);
    printf("Linked List Insert Previous:\n");
    print_list(head);

    node* insert_n = add_node(NULL, 1000);
    head = insert_next(head, insert_n);
    printf("Linked List Insert Next:\n");
    print_list(head);

    node* insert_m = add_node(NULL, -1000);
    int index = 6;
    head = insert_middle(head, insert_m, index);
    printf("Linked List Insert at index %d:\n", index);
    print_list(head);

    free_node(head);

    return 0;
}
