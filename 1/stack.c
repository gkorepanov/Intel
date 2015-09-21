#include "stack.h"

bool empty(struct stack* current_element) {
	return (current_element == NULL);
};
void push(int value, struct stack** current) {
	struct stack* head = (struct stack*)malloc(sizeof(struct stack));
	head->value = value;
	head->next = *current;
	*current = head;
};

int pop(struct stack** current_element) {
	if (empty(*current_element)) return 0;
	int value = (*current_element)->value;
	*current_element = (*current_element)->next;
	return value;
};




