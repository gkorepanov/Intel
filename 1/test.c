#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {
    printf("Testing a stack.h lib:\nPrint a row of int numbers (-3 is end of row):\n");
    int number = 1;
    
    stack_t* stack;   
    stack = malloc(sizeof(stack_t)); // this can be inside ctor.
    
    stack_ctor(stack);
    
    scanf("%d", &number);
    
    while (number+3) {
        stack_push(stack, number);
        printf("\nPushed number %d.\n\n", number);
        stack_dump(stack);
        scanf("%d", &number);     
    }

    while(!is_empty(stack)) {
        printf("\nTop element: %d\n\n", stack_top(stack));
        stack_pop(stack);
        stack_dump(stack);
    }
    
    stack_dtor(stack);

    stack_dump(stack);

    return 0;
}


