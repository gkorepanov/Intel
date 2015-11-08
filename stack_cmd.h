// Template: CMD_(number, word, number of arguments, code)

CMD_(1, push, 1, {
    fread(&operands[0], 1, sizeof(int), source);
    stack_push(&main_stack, operands[0]);
})

CMD_(2, add, 0, { 
    int a = stack_pop(&main_stack);
    int b = stack_pop(&main_stack);
    stack_push(&main_stack, a+b);
})

CMD_(3, sub, 0, { 
    int a = stack_pop(&main_stack);
    int b = stack_pop(&main_stack);
    stack_push(&main_stack, a-b);
})

CMD_(4, mul, 0, { 
    int a = stack_pop(&main_stack);
    int b = stack_pop(&main_stack);
    stack_push(&main_stack, a*b);
})

CMD_(5, top, 0, { 
    printf("%d\n", stack_top(&main_stack));
})

CMD_(6, pop, 0, { 
    printf("%d\n", stack_pop(&main_stack));
})
