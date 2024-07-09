#include "stack.h"
#define EMPTY_VAL -1

struct stack * stack_create(int max_num_of_elem, clone_t create_clone, destroy_t create_destroy,
 print_t create_print){
    struct stack *stack;
    stack = (struct stack*)malloc(sizeof(struct stack));
    //destroy_t elem_destroy = create_destroy;
    //clone_t elem_clone = create_clone;
    //print_t elem_print = create_print;

    stack->clone_func = create_clone;
    stack->destroy_func = create_destroy;
    stack->print_func = create_print;

    stack->maxSize = max_num_of_elem;
    stack->elem_size = sizeof(elem_t); 
    stack->headIndex = EMPTY_VAL;
    //initialize as -1, to be changed by push and pop. (real starting value should be 0
    stack->nodes = (elem_t*)calloc(stack->maxSize,stack->elem_size);

    return stack;
}
// [0] 1 2 3 4 ... [29]
// node[0] bottom of the stack
//node[30]

int stack_destroy(struct stack *stack){
    //delete data in stack and delete nodes array
    for(int i=0; i<=(stack->headIndex); i++){
        stack->destroy_func(stack->nodes[i]);
        //TODO check about success or failure
    }
    free(stack->nodes);
    free(stack);

    return 1;
}

void stack_pop(struct stack *stack){
    if(stack->headIndex>=0){
        stack->destroy_func(stack->nodes[stack->headIndex]);
        stack->headIndex--;
    }
}


elem_t* stack_peek(struct stack *stack){
    if(stack->headIndex>=0){
        return stack->nodes[stack->headIndex];
    } else {
        return NULL;
    }
}

size_t stack_size(struct stack* original_stack){
/*    size_t size=0;



    if (stack->headIndex){



    }




    if (original_stack->nodes!=NULL){ // possibly NOT NEEDED ? made for of Error-Handling
        while (*((original_stack->nodes)+(size*original_stack->elem_size))!=0){
            size++;
        }
    }
    *//**
     * implementation by going backwards
     *
    int size=0;
    while (*((original_stack.nodes)+(original_stack.maxSize*size*original_stack.elem_size)-(i*size*original_stack.elem_size))!=0){
        size++;
    }
    **//*
    return size;*/
    return (size_t)(original_stack->headIndex+1);
}

int stack_push(struct stack* stack, elem_t* new_elem){
    int condition=FAIL;
    int numOfElem=stack_size(stack);
    if (numOfElem==stack->maxSize){
        //printf("push fail\n\n");
    }
    else if(numOfElem<stack->maxSize){
        stack->nodes[stack->headIndex+1]= new_elem;
        stack->headIndex++;
        condition=SUCCESS;
      /*  *stack.nodes=new_elem;
        / implementation by pushing all down one
   / verify numOfElem doesnt deviate from the size.
        while(numOfElem>0){
            elem_t* originalLocation=(stack.nodes)+((numOfElem-1)*stack.elem_size);
            elem_t* pushingToLocation=(stack.nodes)+((numOfElem)*stack.elem_size);
            numOfElem--;
            *pushingToLocation=*originalLocation;
        }*
    }
     different implenetations
     * //reversed
     * else{
        elem_t* newElem = (stack.nodes)+((numOfElem-1)*stack.elem_size);
        *newElem=new_elem;
    }
     *
     * //non-reversed
     *    else{
        elem_t* elem_location = (stack.nodes)+((stack.maxSize-1-numOfElem)*stack.elem_size);
        *elem_location=*new_elem; //possible seg-fault ?
    }
     *
     *
     *
     *
     *
     *
     *
     */
    }

    return condition;
}

bool stack_is_empty(struct stack* original_stack){
    bool is_empty=false;
    if (original_stack->headIndex==EMPTY_VAL){
        is_empty=true;
    }
/*    if ( (*(original_stack.nodes)!=0) || original_stack.nodes==NULL ){ //TODO confirm
        is_empty=false;
    }*/
    return is_empty;
}

void stack_print(struct stack* stack){ //reversed ?
    //elem_t* stackElement;
    for (int numOfElements=(int)stack_size(stack); numOfElements>0; numOfElements--){
        //stackElement = stack->nodes[numOfElements-1];
        //stack->print_func(stackElement);
        stack->print_func(stack->nodes[numOfElements-1]);
        //stack->print_func(stack->nodes + stack->elem_size*(numOfElements-1));
    }
/*
while(numOfElements>0){
    elem_t* stackElement=(stack.nodes+(numOfElements-1)*stack.elem_size);
    stack.print_func(stackElement);
    numOfElements--;
}*/
//reversed implementation
/**
    while(numOfElements>0){
        elem_t* stackElement=(stack.nodes+(numOfElements-1)*stack.elem_size);
        elem_print(stackElement);
        numOfElements--;
    }

**/
}

size_t stack_capacity(struct stack* stack){
/*    size_t capacity;
    size_t currentSize=stack_size(stack);
    if (stack_empty(stack)){
        capacity=(size_t)stack->maxSize;
    }
    if (currentSize!=0){
        capacity=(stack->maxSize-currentSize);
    }
    if (stack->nodes==NULL){
        capacity=0;
    }*/
    return (size_t)(stack->maxSize -stack_size(stack));
}
