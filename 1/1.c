#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"



int check(int kind, struct stack** current_element, bool is_opening);
bool if_bracket(char symbol, bool* is_opening, int* kind, int number_of_types, char* opening, char*  closing);
int read(int number_of_types, char* opening, char*  closing); // 0 - right 1 - error 2 - wrong; had to leave reading from input here for one-by-one input
void print_result(int result_code);
char get_symbol(); // '\n' must be a sign of the end of the brackets sequence

bool if_bracket(char symbol, bool* is_opening, int* kind, int number_of_types, char* opening, char*  closing) {
	int i;
	for (i = 0; i < number_of_types; i++) {
		if (opening[i] == symbol) {
			*is_opening = 1;
			*kind = i + 1;
			return 1;
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
	printf("Achieved.");
	return 0;
};

char get_symbol() { // '\n' must be a sign of the end of the brackets sequence
	return fgetc(stdin);
};

int read(int number_of_types, char* opening, char*  closing) {
	char symbol;
	bool is_opening;
	int kind;
	struct stack* current_element = NULL;

	symbol = get_symbol();

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
				break;
	}
	}
};

int main() {
#define number_of_types 4
	char opening[number_of_types] = { '(', '[', '{', '<' };
	char closing[number_of_types] = { ')', ']', '}', '>' };
	int result_code = read(number_of_types, opening, closing);
	print_result(result_code);
	return 0;
};
