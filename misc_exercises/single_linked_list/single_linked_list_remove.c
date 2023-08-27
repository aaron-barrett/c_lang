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

node* remove_head(node** head){
    node* remove = *head;
    *head = (*head)->n;
    remove->n = NULL;
    return remove;
}

node* remove_prev(node** head, node* current){
    if((*head) == NULL)
        return NULL;
    node* remove = NULL;
    if ((*head) == current)
        remove = remove_head(head);
    else {
        node* temp = *head;
        while(temp->n != current)
            temp = temp->n;
        remove = temp->n;
        temp->n = temp->n->n;
        remove->n = NULL;
    }
    return remove;
}

node* remove_next(node** head){
    node* remove = (*head)->n;
    if((*head)->n != NULL)
        (*head)->n = (*head)->n->n;
    remove->n = NULL;
    return remove;
}

node* remove_end(node** head){
    if(head == NULL)
        return NULL;
    if ((*head)->n == NULL){
        node* remove = (*head);
        (*head) = NULL;
        return remove;
    }
    node* temp = *head;
    while(temp->n->n != NULL)
        temp = temp->n;
    node* remove = temp->n;
    temp->n = NULL;
    return remove;
}

node* remove_middle(node** head, int index){
    if (head == NULL)
        return NULL;
    int size = count_node(*head);
    node* remove = NULL;
    if (index == 0)
        remove = remove_head(head);
    else if (index >= size)
        remove = remove_end(head);
    else{
        node* temp = *head;
        for(int i = 0 ; i < index-1 ; i++)
            temp = temp->n;
        remove = remove_next(&temp);
    }
    return remove;
}


int main(){

    node* head = create_linked_list(6,10);
    printf("Linked List: \n");
    print_list(head);

    node* remove_h = remove_head(&head);
    printf("Linked List Remove Head:\n");
    print_list(head);
    printf("Remove node:\n");
    print_list(remove_h);

    node* remove_p = remove_prev(&head, head->n);
    printf("Linked List Remove Prev:\n");
    print_list(head);
    printf("Remove node:\n");
    print_list(remove_p);

    node* remove_n = remove_next(&head);
    printf("Linked List Remove Next:\n");
    print_list(head);
    printf("Remove node:\n");
    print_list(remove_n);

    int index = 1;
    node* remove_m = remove_middle(&head, index);
    printf("Linked List Remove at index %d:\n", index);
    print_list(head);
    printf("Remove node:\n");
    print_list(remove_m);

    free_node(head);
    free_node(remove_h);
    free_node(remove_p);
    free_node(remove_n);
    free_node(remove_m);

    return 0;
}
