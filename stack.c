#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


void stack_ctor(stack_t* This) {
    assert(This && "Passed NULL pointer to constructor");

    This->size = 0;
    This->head = (list_t*)calloc(1, sizeof(list_t));
    list_ctor(This->head, 0, NULL);

    assert(stack_ok(This));
}

void stack_dtor(stack_t* This) {
    assert(stack_ok(This) && "Passed NULL pointer to destructor");

    This->size = 0;
    list_dtor(This->head);
}

void stack_push(stack_t* This, int value) {
    assert(stack_ok(This) && "Passed NULL ptr to pusher");

    list_put(This->head, value);
    (This->size)++;

    assert(stack_ok(This));
}

int stack_top(stack_t* This) {
    assert(stack_ok(This));
    assert(This->size && "Retrieving value from empty stack!");

    return list_get(This->head);
}

int stack_pop(stack_t* This) {
    assert(stack_ok(This));
    assert(This->size && "Removing element from empty stack!");
    int value = list_get(This->head);
    list_rm(This->head);
    (This->size)--;
    assert(stack_ok(This));
    return value;
}

bool is_empty(stack_t* This) {
    return !(This->size);
}

bool stack_ok(stack_t* This) {
    return This &&
           (This->size>=0) &&
           list_ok(This->head);
}

void stack_dump(stack_t* This) {
    printf("-----------------------------------\n"\
           "STACK:\nsize: %d\n", This -> size);
    list_dump(This->head);
    printf("-----------------------------------\n");
}
