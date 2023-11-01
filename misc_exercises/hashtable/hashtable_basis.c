#include <stdio.h>
#include <stdlib.h>

#define MAXHASH 100

typedef struct item item;
struct item {
    int key;
    int data;
};

int generate_hash_code(int data)
{
    return data % MAXHASH;
}

item** hash_init()
{
    item** h = malloc(sizeof(item*) * MAXHASH);
    for (unsigned i = 0 ; i < MAXHASH; i++)
        h[i] = NULL;
    return h;
}

void free_hash(item** h)
{
    for (unsigned i = 0 ; i < MAXHASH; i++)
        free(h[i]);
    free(h);
}

void print_hash(item** h)
{
    for (unsigned i = 0 ; i < MAXHASH; i++)
        if ( h[i] != NULL)
            printf("key:\t%d\t\tdata:\t%d\n", h[i]->key, h[i]->data);
}

void add_item(item** h, int data)
{
    int key = generate_hash_code(data);
    if (h[key] == NULL)
    {
        item* new_item =  malloc(sizeof(item));
        new_item->key = key;
        new_item->data = data;
        h[key] = new_item;
    }
    else 
        fprintf(stderr, "Error: No suport for redundant entries.\n");
}

void delete_item(item** h, int data)
{
    int key = generate_hash_code(data);
    if (h[key] != NULL)
    {
        free(h[key]);
        h[key] = NULL;
    }
    else 
        fprintf(stderr, "Error: No entry with key \"%d\" to delete.\n", key);
}

void search_item(item** h, int data)
{
    int key = generate_hash_code(data);
    if (h[key] != NULL)
        printf("Data Found\nData:\t%d \t\tkey:\t%d\n", data, key);
    else 
        printf("Data NOT Found\nData:\t%d \t\tkey:\t%d\n", data, key);
}


int main()
{
    item** hash = hash_init();
    add_item(hash, 100);
    add_item(hash, 105);
    add_item(hash, 199);
    add_item(hash, 99);
    printf("After setup:\n");
    print_hash(hash);
    delete_item(hash, 105);
    delete_item(hash, 6);
    printf("After delete:\n");
    print_hash(hash);
    printf("Searching:\n");
    search_item(hash, 100);
    search_item(hash, 101);
    free_hash(hash);
    return 0;
}

