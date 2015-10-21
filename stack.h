#include "list.h"
#ifndef STACK
#define STACK

typedef struct {
    int size;
    list_t* head;
} stack_t;

void stack_ctor(stack_t* This);
void stack_dtor(stack_t* This);


void stack_push(stack_t* This, int value);
int stack_pop(stack_t* This);

int stack_top(stack_t* This);
int is_empty(stack_t* This);
int stack_ok(stack_t* This);

void stack_dump(stack_t* This);

#endif
