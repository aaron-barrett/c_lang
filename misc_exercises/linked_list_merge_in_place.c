#include <stdio.h>
#include <stdlib.h>

typedef struct node node; 
struct node{
    int data;
    node* neighbor;
};

node* create_linked_list(unsigned size, int offset){
    if (size <1)
        return NULL;
    node* head = (node*)malloc(sizeof(node));
    node* temp = head;
    for(int i = 0 ; i < size ; i++){
        head->data = i + offset;
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

int sorted(node*head){
    while(head->neighbor != NULL){
        if (head->neighbor->data < head->data)
            return -1;
        head = head->neighbor;
    }
    return 1;
}

node* merge(node* one, node* two){
    if (one == NULL || two == NULL)
        return one != NULL ? one : two;

    int size = count_node(one) + count_node(two);

    if (one->data > two->data){
        node* h = one;
        one = two ; 
        two = two->neighbor;
        one->neighbor = h;
    }
    
    node* hold = one;

    for(int i = 0 ; i < size - 1 ; i++){
        if (two == NULL || one == NULL)
            break;
        else if (one->neighbor == NULL){
            one->neighbor = two;
            two = two->neighbor;
            one->neighbor->neighbor = NULL;
            one = one->neighbor;
        }
        else{
            if(one->neighbor->data <= two->data){
                if(one->neighbor->neighbor != NULL && one->neighbor->neighbor->data <= two->data)
                    one = one->neighbor;
                else{
                    node* h = one->neighbor->neighbor;
                    one->neighbor->neighbor = two;
                    two = two->neighbor;
                    one = one->neighbor;
                    one->neighbor->neighbor = h;
                }
            }
            else{
                node* h = one->neighbor;
                one->neighbor = two;
                two = two->neighbor;
                one = one->neighbor;
                one->neighbor = h;
            }
        }
    }
    return hold;
}

int main(){

    node* head1 = create_linked_list(1, 10);
    node* head2 = create_linked_list(3, -10);

    printf("List 1: \n");
    print_list(head1);

    printf("List 2: \n");
    print_list(head2);

    node* head = merge(head1, head2);
    if (sorted(head) == -1)
        printf("Fail: Linked List NOT Sorted.\n");
    else 
        printf("Success: Link List Sorted!\n");

    printf("Free linked list: \n");
    free_node(head);

    return 0;
}
