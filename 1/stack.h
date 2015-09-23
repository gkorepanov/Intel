#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
	SUGGETION: I'd better implement stack on array in this case.
		   What's the reason to use list? If you have a lot of "push"s and "pop"s, 
		   there will be many memory allocations and "free"s.
		   You may use static array, if you anticipate certain number of element, or array with changing size.
		   In last case, I mean something like c++'s <vector>. But in c you have to implement yourself.

		   Nevetheless, on lectures Ilya Ded will tell you about stack on static array, as far as I know.
*/

struct stack {
	int value;
	struct stack* next;
};
/*
	SUGGESTION: Use here typedef instead of using struct stack everywhere.
*/
void push(int value, struct stack** current);
int pop(struct stack** current_element);
bool empty(struct stack* current_element);
/*SUGGESTION: I'd call the last function is_empty. To my mind, empty means to clear stack.
*/
