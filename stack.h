#ifndef STACK_H
#define STACK_H

#include <string.h>
#include "common.h"
typedef void * elem_t; //aliases generic element create a new type called elem_t
typedef elem_t (*clone_t) (elem_t e);
//aliases a pointer to a cloning function with the input (elem_t) and a return type elem_t - creates a new type called elem_t
typedef void (*destroy_t) (elem_t e ); //aliases a pointer to a destroyer function with the input (elem_t)
typedef void (*print_t) (elem_t e );  //aliases a pointer to a printer function with the input (elem_t)

struct stack{
    elem_t* nodes;
    int headIndex;
    int maxSize ;
    int elem_size;
    destroy_t destroy_func;
    print_t print_func;
    clone_t clone_func;
};

struct stack * stack_create(int max_num_of_elem, clone_t create_clone, destroy_t create_destroy, print_t create_print);
size_t stack_size(struct stack* original_stack);
int stack_push(struct stack* stack, elem_t* new_elem);
bool stack_is_empty(struct stack* original_stack);
void stack_print(struct stack* stack);
size_t stack_capacity(struct stack* stack);
int stack_destroy(struct stack *stack);
void stack_pop(struct stack *stack);
elem_t* stack_peek(struct stack *stack);

#endif