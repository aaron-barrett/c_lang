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

node* remove_prev(node* head){
    if (head == NULL)
        return head;
    node* remove = head->p;
    if(head->p != head){
        head->p = head->p->p;
        head->p->n = head;
        remove->p = remove;
        remove->n = remove;
    }
    return remove;
}

node* remove_next(node* head){
    if (head == NULL)
        return head;
    node* remove = head->n;
    if(head->n != head){
        head->n = head->n->n;
        head->n->p = head;
        remove->n = remove;
        remove->p = remove;
    }
    return remove;
}

node* remove_beginning(node** head){
    node* remove = (*head);
    if((*head)->p != (*head)){
        (*head)->p->n = (*head)->n;
        (*head)->n->p = (*head)->p;
        (*head) = (*head)->n;
        remove->n = remove;
        remove->p = remove;
    }
    return remove;
}

node* remove_mid(node** head, int index){
    int size = count_dll_circular(*head);
    node* remove = NULL;
    if (size == 0)
        return NULL;
    if (index >= size)
        remove = remove_prev(*head);
    else if (index == 0)
        remove = remove_beginning(head);
    else {
        node* temp = (*head);
        for(int i = 0 ; i < index -1; i++)
            temp = temp->n;
        remove = remove_next(temp);
    }
    return remove;
}

int main(){

    node* head = create_dll_circular(5, 10);
    printf("Circular Double Linked List:\n");
    print_dll_circular(head);

    node* remove_p = remove_prev(head);
    printf("Circular Double Linked List Remove Prev:\n");
    print_dll_circular(head);
    printf("Remove Node:\n");
    print_dll_circular(remove_p);

    node* remove_n = remove_next(head);
    printf("Circular Double Linked List Remove Next:\n");
    print_dll_circular(head);
    printf("Remove Node:\n");
    print_dll_circular(remove_n);

    int index = 1;
    node* remove_m = remove_mid(&head, index);
    printf("Circular Double Linked List Remove Middle at %d:\n", index);
    print_dll_circular(head);
    printf("Remove Node:\n");
    print_dll_circular(remove_m);

    printf("Circular Double Linked List Print Reverse %d:\n", index);
    print_dll_circular_reverse(head);

    free_dll_circular(head);
    free_dll_circular(remove_p);
    free_dll_circular(remove_n);
    free_dll_circular(remove_m);

    return 0 ;
}
