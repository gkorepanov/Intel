#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
/* QUESTION[0]: How to identify the last element of stack if using
NULL pointer is prohibited? Look elem_ctor(), elem_dtor(), stack_ok(), elem_ok() for
corresponding lines, please! */

const value_t default_value = -1; /* to initialize new elements
                                    QUESTION[1]: Am I right to put it here, in stack.c?*/


void stack_ctor(stack_t* This) { // QUESTION[2]: Should I malloc memory in c-tor?
    assert(This);
    This->size = 0;
    This->head = malloc(sizeof(elem_t));
    elem_ctor((This->head));
}

void stack_dtor(stack_t* This) { // QUESTION[3]: Should I free memory in d-tor? 
    assert(This);
    elem_dtor(This->head); // Look elem_dtor() for a question
    free(This);
}

void stack_push(stack_t* This, value_t value) {
    assert(stack_ok(This)); // QUESTION[4]: Am I right using that expression in the beginning of each function?

    elem_t* new_elem = malloc(sizeof(elem_t));
    elem_ctor(new_elem);

    new_elem->value = value;
    new_elem->next = This->head;
    This->head = new_elem;
    (This->size)++;
}

value_t stack_top(stack_t* This) {
    assert(stack_ok(This));
    return This->head->value;
}

int stack_pop(stack_t* This) {
    assert(stack_ok(This));
    if (!(This->size)) return 1; 
    elem_t* temp = This->head->next;
    free(This->head);
    This->head = temp;
    (This->size)--;
    return 0;
}

int is_empty(stack_t* This) {
    return !(This->size);
}

int stack_ok(stack_t* This) {
    return (This ? 1 : 0) &&
           elem_ok(This->head);
}

void stack_dump(stack_t* This) {
    printf("DUMP:\ntype: stack_t\nsize: %d\n", This -> size);
    elem_dump(This->head);
}

void elem_dump(elem_t* This) {
    printf("Value: %d\n", This->value);
    if (This->next) 
        elem_dump(This->next);
}

int elem_ok(elem_t* This) {
    return This ? 1 : 0; // [0]: I can't check here if (This->next == 0) cause it may point to last NULL element of stack
}

void elem_ctor(elem_t* This) { // Same question to [2]
    assert(This);
    This->value = default_value;
    This->next = NULL; // [0]: how do I initialize the pointer? 
}

void elem_dtor(elem_t* This) {
    if (This->next) 
        elem_dtor(This->next); /*  Here is emplementation of recursive remove of list. Is it acceptable or d-tor must only
                                   fill values with something/free memory[3]? */
    if (This)
        free(This); // Same question to [3]
}
