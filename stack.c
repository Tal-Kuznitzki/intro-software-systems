#include "stack.h"
Stack stack_create(int max_num_of_elem, elem_t* create_clone, void* create_destroy, void* create_print){
    Stack stack;
    //destroy_t elem_destroy = create_destroy;
    //clone_t elem_clone = create_clone;
    //print_t elem_print = create_print;


    stack.clone_func=create_clone;
    stack.destroy_func=create_destroy;
    stack.print_func=create_print;

    stack.maxSize = max_num_of_elem;
    stack.elem_size = sizeof(elem_t); 
    stack.headIndex = 0;
    stack.nodes = calloc(stack.maxSize,stack.elem_size);

    return stack;
}


int stack_destroy(Stack *stack){
    //delete data in stack and delete nodes array
    for(int i=0; i<(stack->headIndex); i++){
        stack->elem_destroy(stack->nodes[i]);
    }
    free(stack);

    return 1;
}

void stack_pop(Stack *stack){
    if(stack->headIndex>0){
        stack->elem_destroy(stack->nodes[stack->headIndex]);
        stack->headIndex--;
    }
}


elem_t* stack_peek(Stack *stack){
    if(stack->headIndex>0){
        return stack->nodes[stack->headIndex];
    } else {
        return NULL;
    }
}



size_t stack_size(Stack original_stack){
    size_t size=0;
    if (original_stack.nodes!=NULL){ //TODO possibly NOT NEEDED ? made for of Error-Handling
        while (*((original_stack.nodes)+(size*original_stack.elem_size))!=0){
            size++;
        }
    }
    /**
     * implementation by going backwards
     *
    int size=0;
    while (*((original_stack.nodes)+(original_stack.maxSize*size*original_stack.elem_size)-(i*size*original_stack.elem_size))!=0){
        size++;
    }
    **/
    return size;
}

int stack_push(Stack stack, elem_t* new_elem){
    int condition=SUCCESS;
    int numOfElem=stack_size(stack);
    if (numOfElem==stack.maxSize){
        condition=FAIL;
    }
    else{ // implementation by pushing all down one

   // verify numOfElem doesnt deviate from the size.
        while(numOfElem>0){
            elem_t* originalLocation=(stack.nodes)+((numOfElem-1)*stack.elem_size);
            elem_t* pushingToLocation=(stack.nodes)+((numOfElem)*stack.elem_size);
            numOfElem--;
            *pushingToLocation=*originalLocation;
        }
        *stack.nodes=new_elem;
    }


    /** different implenetations
     * //reversed
     * else{
        elem_t* newElem = (stack.nodes)+((numOfElem-1)*stack.elem_size);
        *newElem=new_elem;
    }
     *
     * //non-reversed
     *    else{
        elem_t* elem_location = (stack.nodes)+((stack.maxSize-1-numOfElem)*stack.elem_size);
        *elem_location=*new_elem; //TODO possible seg-fault ?
    }
     *
     *
     *
     *
     *
     *
     *
     * **/
         return condition;
}

bool stack_empty(Stack original_stack){
    bool is_empty=true;
    if ( (*(original_stack.nodes)!=0) || original_stack.nodes==NULL ){ //TODO confirm
        is_empty=false;
    }
    return is_empty;


}

void stack_print(Stack stack){ //reversed ?
int numOfElements=stack_size(stack);
while(numOfElements>0){
    elem_t* stackElement=(stack.nodes+(numOfElements-1)*stack.elem_size);
    stack.print_func(stackElement);
    numOfElements--;
}

//reversed implementation
/**
    while(numOfElements>0){
        elem_t* stackElement=(stack.nodes+(numOfElements-1)*stack.elem_size);
        elem_print(stackElement);
        numOfElements--;
    }

**/

}

size_t stack_capacity(Stack stack){
    //TODO check how to return Error or how to differentiate between 0 in stackSize and failure
    size_t capacity;
    size_t currentSize=stack_size(stack);
    if (stack_empty(stack)){
        capacity=(size_t)stack.maxSize;
    }
    if (currentSize!=0){
        capacity=stack.maxSize-currentSize;
    }
    if (stack.nodes==NULL){ //TODO confirm
        capacity=0;
    }
    return capacity;



}
