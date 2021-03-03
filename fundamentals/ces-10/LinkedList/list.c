#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define NDEBUG

#include "list.h"

/************** STATIC FUNCTIONS ************************/
// functions not visible outside this file

// Create a new node
//
// Return:
// - NULL on failure
static struct node* create_node(size_t key, long int value, struct node* next) 
{
    struct node *n = (struct node*) malloc(sizeof(struct node));

    if (n != NULL) 
    {
        n -> key = key;
        n -> value = value;
        n -> next = next;
    }

    return n;
}

// Print a node as '[key]=value'
static void print_node(struct node *n) 
{
    printf("[%zu]=%ld", n->key, n->value);
}


/******************* NON STATIC FUNCTIONS *****************/
// functions visible outside this file

// Print the list values using the function print_node
void print_list(struct list* list) 
{
    struct node *n = (list==NULL) ? NULL : list->head;  // if list == NULL, list->head does not work

    while(n != NULL) 
    {
        print_node(n);
        printf("\n");
        n = n->next;
    }
}

// Create a new empty list in heap
//
// Return:
// - NULL on failure
struct list *new_list() 
{
    struct list *p = (struct list*)malloc(sizeof(struct list));

    if (p != NULL) 
    {
        // Initialization (or calloc)
        p->head = p->tail = NULL;
        p->size = 0;
    }

    return p;
}

// Delete all the node's and list structures
void delete_list(struct list *lista) 
{
    if (lista == NULL)
        return;

    struct node *n = lista->head;
    struct node *back;

    while (n != NULL) 
    {
        back = n;
        n = n->next;
        free(back);
    }

    free(lista);
}

// Add a new (key,value) in the end of the list
//
// Return:
// - NULL on failure
// - pointer to (key,value) node on success
struct node *append(struct list* list, size_t key, int long value) 
{
    struct node *new_node = create_node(key, value, NULL);
    
    if (new_node != NULL)
    {
        assert(new_node != NULL);
        assert(new_node->key == key);
        assert(new_node->value == value);
        assert(new_node->next == NULL);

        // update the list structure
        if (list->head == NULL)
            list->head = new_node;

        if (list->tail != NULL)
            list->tail->next = new_node;
        
        list->tail = new_node;
        list->size++;
    }

    return new_node;
}

// Compute an elementwise operation (op) over nodes
//
// Return:
// - NULL on failure
// - list with the result
struct list* elementwise_op(el_wise_op_t op, struct node *n1, struct node *n2) 
{
    struct list *res_list = new_list();
    if (res_list == NULL)
        return NULL;

    while (n1 != NULL || n2 != NULL)
    {
        if (n1 == NULL && n2 != NULL)
        {
            append(res_list, n2->key, n2->value);
            n2 = n2->next;
        }
        if (n2 == NULL && n1 != NULL)
        {
            append(res_list, n1->key, n1->value);
            n1 = n1->next;
        }
        if (n1 != NULL && n2 != NULL)
        {
            if (n1->key == n2->key)
            {
                if (n1->value + n2->value != 0)
                {
                    append(res_list, n1->key, op(n1->value, n2->value));
                    n1 = n1->next;
                    n2 = n2->next;
                }
                else
                {
                    n1 = n1->next;
                    n2 = n2->next;
                }
            }
            else if (n1->key > n2->key)
            {
                append(res_list, n2->key, n2->value);
                n2 = n2->next;
            }
            else 
            {
                append(res_list, n1->key, n1->value);
                n1 = n1->next;
            }
        }
    }

    return res_list;
}



