// Template: CMD_(number, word, number of arguments, code)

CMD_(0, end, 0, {})

CMD_(1, push, 1, {
    stack_push(This->stack, *(int*)(This->cmds+This->pos+1));
})

CMD_(2, add, 0, { 
    int a = stack_pop(This->stack);
    int b = stack_pop(This->stack);
    stack_push(This->stack, a+b);
})

CMD_(3, sub, 0, { 
    int a = stack_pop(This->stack);
    int b = stack_pop(This->stack);
    stack_push(This->stack, a-b);
})

CMD_(4, mul, 0, { 
    int a = stack_pop(This->stack);
    int b = stack_pop(This->stack);
    stack_push(This->stack, a*b);
})

CMD_(5, print, 0, { 
    printf("Last element: %d\n", stack_top(This->stack));
})

CMD_(6, pop, 0, { 
    stack_pop(This->stack);
})

CMD_(7, dump, 0, {
    stack_dump(This->stack);
})
