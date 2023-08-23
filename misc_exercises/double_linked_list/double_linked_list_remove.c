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

node* remove_beginning(node** head){
    node* remove = *head;
    if((*head)->n != NULL){
        (*head) =(*head)->n;
        (*head)->p = NULL;
        remove->n = NULL;
        remove->p = NULL;
    }
    return remove;
}

node* remove_prev(node* head){
    if(head->p == NULL)
        return NULL;
    node* remove = head->p;
    if (remove->p != NULL){
        head->p->p->n = head;
        head->p = head->p->p;
        remove->n = NULL;
        remove->p = NULL;
    }
    return remove;
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

node* remove_end(node* head){
    node* remove = head;
    while(remove->n != NULL)
        remove = remove->n;
    remove->p->n = NULL;
    remove->p = NULL;
    return remove;
}

node* remove_mid(node** head, int index){
    int size = count_dll(*head);
    node* remove = NULL;
    if (size == 0)
        return NULL;
    if (index >= size)
        remove = remove_end(*head);
    else if (index == 0)
        remove = remove_beginning(head);
    else {
        node* temp = (*head);
        for(int i = 0 ; i < index - 1; i++)
            temp = temp->n;
        remove = remove_next(temp);
    }
    return remove;
}

int main(){

    node* head = add_node(NULL, -1);
    head = add_node(head, 8);
    head = add_node(head, 7);
    head = add_node(head, -10);
    head = add_node(head, 100);

    printf("Double Linked List:\n");
    print_dll(head);

    node* remove_p = remove_prev(head->n->n);
    printf("Double Linked List Remove Prev:\n");
    print_dll(head);
    printf("Removed Node:\n");
    print_dll(remove_p);

    node* remove_n = remove_next(head);
    printf("Double Linked List Remove Next:\n");
    print_dll(head);
    printf("Removed Node:\n");
    print_dll(remove_n);

    int index = 2;
    node* remove_m = remove_mid(&head,index);
    printf("Double Linked List Remove at %d:\n", index);
    print_dll(head);
    printf("Removed Node:\n");
    print_dll(remove_m);


    free_dll(head);
    free_dll(remove_p);
    free_dll(remove_n);
    free_dll(remove_m);

    return 0 ;
}
