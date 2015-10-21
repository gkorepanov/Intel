#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {
    printf("Testing a stack.h lib:\nPrint a row of int numbers (-3 is end of row):\n");

    int number = 0;
    
    stack_t stack;   
    stack_ctor(&stack);
    
    scanf("%d", &number);
    
    while (number+3) {
        stack_push(&stack, number);
        printf("\nPushed number %d.\n\n", number);
        stack_dump(&stack);
        scanf("%d", &number);     
    }

    while(!is_empty(&stack)) {
        printf("\nTop element: %d ", stack_top(&stack));

        stack_pop(&stack);
        printf("has been successfully removed from stack.\n");
        stack_dump(&stack);
    }

    stack_dtor(&stack);

    printf("Stack has been safely destructed, no errors have been revealed.\n");
    return 0;
}


