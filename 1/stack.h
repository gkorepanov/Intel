#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



struct stack {
	int value;
	struct stack* next;
};

void push(int value, struct stack** current);
int pop(struct stack** current_element);
bool empty(struct stack* current_element);

