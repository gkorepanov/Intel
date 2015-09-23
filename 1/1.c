#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>// SUGGESTION: I don't think it is neccesary
#include "stack.h"

/*FYI:
	Note about my comments.
	TODO is a thing, I need you to correct in your code.
	SUGGESTION is a thing, I would correct in code. But if you clarify, why you want to keep that variant, I will agree.
	QUESTION is a thing, you should answer in comments or at classes(after lecture).
*/

int check(int kind, struct stack** current_element, bool is_opening);
bool if_bracket(char symbol, bool* is_opening, int* kind, int number_of_types, char* opening, char*  closing);
int read(int number_of_types, char* opening, char*  closing); // 0 - right 1 - error 2 - wrong; had to leave reading from input here for one-by-one input
void print_result(int result_code);
char get_symbol(); // '\n' must be a sign of the end of the brackets sequence

/*
	TODO: Add processing expression with other symbols.
	      Like: (1+1)*[(2*2)^[3-2]]
	      The task is the same, just to check the validity of bracket expression
*/

/*
	SUGGESTION: I was wonderring, whether you really need to use number_of_types.
	Do you expect some scaling of this task? Will this variable ever change in future?
	My Suggestion is to make it constant.
*/

bool if_bracket(char symbol, bool* is_opening, int* kind, int number_of_types, char* opening, char*  closing) {
	int i;
	for (i = 0; i < number_of_types; i++) {
		if (opening[i] == symbol) {
			*is_opening = 1;
			*kind = i + 1; // QUESTION: Why do you need to assign kind into incremented i, not simply i?
			return 1;      // What's wrong if kind == 0 somewhere?
		}
		else if (closing[i] == symbol) {
			*is_opening = 0;
			*kind = i + 1;
			return 1;
		}
	}
	return 0;
};



int check(int kind, struct stack** current_element, bool is_opening) {
	if (is_opening) {
		push(kind, current_element);
		return 1;
	}
	if (empty(*current_element)) return 0;
	int compared = pop(current_element);
	if (compared == kind) return 1;
	printf("Achieved.");// QUESTION: Why do i need to see this, when i input wrong string?
			    // I suppose it's debugging info.	
	return 0;
};

char get_symbol() { // '\n' must be a sign of the end of the brackets sequence
	return fgetc(stdin);
};

int read(int number_of_types, char* opening, char*  closing) {
	/*TODO: Initialize the variables.
		everything you declare must be initialized.
		That's the rule Ilya Ded will tell you later.
		There are some exceptions in this rules. But not in this case.
	*/

	char symbol;
	bool is_opening;
	int kind;
	struct stack* current_element = NULL;

	symbol = get_symbol();// QUESTION: Why do you wrapped fgetc into another function?
			      // Do you expect some new ways to read the string,
			      // to check something in reading fucntion?

	while (symbol != '\n') {
		if (if_bracket(symbol, &is_opening, &kind, number_of_types, opening, closing)) {
			if (!check(kind, &current_element, is_opening)) return 2;
		}
		else if (symbol == ' ');
		else {
			return 1;
		}

		symbol = get_symbol();
	}

	if (!empty(current_element)) return 2;
	return 0;
};

void print_result(int result_code) {
	switch (result_code) {
	case 0: {
				printf("The sequence of brackets is right!\n");
				break;
	}
	case 1: {
				fprintf(stderr, "Wrong format of input string!\n");
				break;
	}
	case 2: {
				printf("Unfortunately, you've typed wrong sequence of brackets.\n");
				break;//QUESTION: If you use stderr in case 1, why not to use it in case 2? 
	}
	}
};

int main() {
/*	FYI: Functions' "disign" is really great. And using result_code, print_result is professional indeed, IMO.
	Also here is a remark about number_of_types.
*/
#define number_of_types 4
	char opening[number_of_types] = { '(', '[', '{', '<' };
	char closing[number_of_types] = { ')', ']', '}', '>' };
	int result_code = read(number_of_types, opening, closing);
	print_result(result_code);
	return 0;
};
