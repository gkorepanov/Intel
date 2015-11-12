// Template: CMD_(number, word, number of arguments, code)

CMD_(0, end, 0, "", {})

CMD_(1, push, 1, "n", {
    stack_push(This->stack, *(int*)(This->cmds+This->pos+1));
})

CMD_(2, push, 1, "r", {})

CMD_(3, pop, 0, "", { 
    stack_pop(This->stack);
})

CMD_(4, pop, 1, "r", {})

CMD_(5, add, 0, "", { 
    int a = stack_pop(This->stack);
    int b = stack_pop(This->stack);
    stack_push(This->stack, a+b);
})

CMD_(6, sub, 0, "", { 
    int a = stack_pop(This->stack);
    int b = stack_pop(This->stack);
    stack_push(This->stack, a-b);
})

CMD_(7, mul, 0, "", { 
    int a = stack_pop(This->stack);
    int b = stack_pop(This->stack);
    stack_push(This->stack, a*b);
})

CMD_(8, print, 0, "", { 
    printf("Last element: %d\n", stack_top(This->stack));
})

CMD_(9, dump, 0, "", {
    stack_dump(This->stack);
})

CMD_(10, mov, 2, "rn", {})

CMD_(11, jmp, 1, "l", {})

CMD_(12, ja, 1, "l", {})

CMD_(13, call, 1, "f", {})

CMD_(13, ret, 0, "", {})
