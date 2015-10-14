#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
/* QUESTION[0]: How to identify the last element of stack if using
NULL pointer is prohibited? Look elem_ctor(), elem_dtor(), stack_ok(), elem_ok() for
corresponding lines, please! */
/*
	Answer: You're talking about last element of list, I suppose. Head(or last element) contains the null pointer to previous or next elem.
*/
const value_t default_value = -1; /* to initialize new elements
                                    QUESTION[1]: Am I right to put it here, in stack.c?
									Answer: It's OK. But why do you need special const for it. Usually they use null or another zero constant 										of type. 
									To my mind, it's bad to scale the class to template class(when it can accept different types of elements). 									*/


/*
FYI: I think, I've found out, why I felt uncertain about list in stack.
	 You use data more complicated structure(list)(which in your implimentation is incomplete) inside stack as skeleton.
	 And you use only the idea of list(pointers and moving pointers).
	 At the first glance, your list implementation and using list are mixed with each other. You implement destructor and constructor for list
	 as it's another abstract structure(not c++ "abstract"), but the idea of using it (how to put elems in list and peek from list) lies on 	 the user of this class(structure).
	 The overall impression is like some functions are not implemented.

SUGGESTION: I don't suggest you to reimplement it with array. If you like list, use it.
			But list should be the list, not only the idea. It would be easy for you to use it and find errors.
			I understand, that it can work fine with this implementation. But we should teach you to construct everything right and clear. 

SUGGESTION: Implement another structure list. In another list.h and list.c. And use it here. 

FYO:		If you are tired of rewriting stack everytime, say it.
			Try to solve another problems with file reading and strings sorting("eugeny onegin").
			To my mind, you can learn and I can teach in this area(OOP) more, than in working with pointers and arrays.
*/

void stack_ctor(stack_t* This) { // QUESTION[2]: Should I malloc memory in c-tor?
    assert(This);				 // ANSWER: Yes, malloc to the stack object. You should initialize your stack. Call the constuctor of your list. There should be empty, 
								 //	but not null list. And stack is respectively empty, not null.
	//About assert. You can pass null object to constructor. You should check after all initializations, 
	//that everything is ok.							
    This->size = 0;
    This->head = malloc(sizeof(elem_t));
    elem_ctor((This->head));
}

void stack_dtor(stack_t* This) { // QUESTION[3]: Should I free memory in d-tor? Answer:Yes.
    assert(This);//why not stack_ok? 				 
    elem_dtor(This->head); // Look elem_dtor() for a question
    free(This);				
}

void stack_push(stack_t* This, value_t value) {
    assert(stack_ok(This)); // QUESTION[4]: Am I right using that expression in the beginning of each function?
							// Answer: Yes, you're right here. Ilya Ded talked about. Moreover, you should check it in the end of function.
							// To confirm, that your actions haven't spoilt the stack.
    elem_t* new_elem = malloc(sizeof(elem_t));
    elem_ctor(new_elem);

    new_elem->value = value;//SUGGESTION: You are using list. I suppose it should be in list's logic.
    new_elem->next = This->head;//To put elem inside it. 
    This->head = new_elem;// 
    (This->size)++;
}

value_t stack_top(stack_t* This) {
    assert(stack_ok(This));
    return This->head->value;
}

int stack_pop(stack_t* This) {
    assert(stack_ok(This));
    if (!(This->size)) return 1; 
    elem_t* temp = This->head->next;
    free(This->head);
    This->head = temp;
    (This->size)--;
    return 0;
}

int is_empty(stack_t* This) {
    return !(This->size);
}

int stack_ok(stack_t* This) {
    return (This ? 1 : 0) &&
           elem_ok(This->head);
}

void stack_dump(stack_t* This) {
    printf("DUMP:\ntype: stack_t\nsize: %d\n", This -> size);
    elem_dump(This->head);
}

void elem_dump(elem_t* This) {
    printf("Value: %d\n", This->value);
    if (This->next) 
        elem_dump(This->next);
}

int elem_ok(elem_t* This) {
    return This ? 1 : 0; // [0]: I can't check here if (This->next == 0) cause it may point to last NULL element of stack
}

void elem_ctor(elem_t* This) { // Same question to [2]
    assert(This);//Same not as in stack_ctor.
    This->value = default_value;
    This->next = NULL; // [0]: how do I initialize the pointer? Answer: With NULL. Later, you will pass it to contructor and get normal object.
}

void elem_dtor(elem_t* This) {
    if (This->next) 
        elem_dtor(This->next); /*  Here is emplementation of recursive remove of list. Is it acceptable or d-tor must only
                                   fill values with something/free memory[3]? */
							// Answer: Of course you must delete all elements of list in one destructor. You implement it right, to my mind.
    if (This)
        free(This); // Same question to [3]
}
