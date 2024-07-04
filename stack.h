
#include <string.h>
#include "common.h"
typedef void * elem_t; //aliases generic element create a new type called elem_t
typedef elem_t (*clone_t) (elem_t e);
//aliases a pointer to a cloning function with the input (elem_t) and a return type elem_t - creates a new type called elem_t
typedef void (*destroy_t) (elem_t e ); //aliases a pointer to a destroyer function with the input (elem_t)
typedef void (*print_t) (elem_t e );  //aliases a pointer to a printer function with the input (elem_t)

typedef struct {
    elem_t* nodes;
    int headIndex;
    int maxSize ;
    int elem_size;
    destroy_t destroy_func;
    print_t print_func;
    clone_t clone_func;
} Stack  ;

Stack stack_create(int max_num_of_elem, elem_t* create_clone, void* create_destroy, void* create_print);
size_t stack_size(Stack* original_stack);
int stack_push(Stack* stack, elem_t* new_elem);
bool stack_empty(Stack* original_stack);
void stack_print(Stack* stack);
size_t stack_capacity(Stack* stack);
int stack_destroy(Stack *stack);
void stack_pop(Stack *stack);
elem_t* stack_peek(Stack *stack);
