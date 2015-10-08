#include "stack.h"

bool is_empty(stack* current_element) {
    return (current_element == NULL);
};
void push(int value, stack** current) {
    stack* head = (stack*)malloc(sizeof(stack));
    head->value = value;
    head->next = *current;
    *current = head;
};

int pop(stack** current_element) {
    if (is_empty(*current_element)) return 0;
    int value = (*current_element)->value;
    stack* temp = *current_element;
    *current_element = (*current_element)->next;
    free(temp);
    return value;
};

void free_stack(stack** current_element) {
    stack* temp;
    while (*current_element) {
        temp = *current_element;
        *current_element = (*current_element)->next;
        free(temp);
    } 
};


