#include <stdlib.h>
#include <stdio.h>
#include<stdbool.h>
#define max_lenght 1000

int i = 0;

struct stack {
	int value;
	struct stack* next;
};


void push(int value, struct stack** current);
bool empty(struct stack* current_element);
int check(int kind, struct stack** current_element, bool is_opening);
void push(int value, struct stack** current);
int pop(struct stack** current_element);

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

bool empty(struct stack* current_element) {
	return (current_element == NULL);
}


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
}

int read(char* string_of_brackets, int number_of_types, char* opening, char*  closing) { // 0 - right 1 - err 2 - wrong
	char symbol;
	bool is_opening;
	int kind;
	struct stack* current_element = NULL;

	symbol = fgetc(stdin);

	while (symbol != '\n') {
		if (if_bracket(symbol, &is_opening, &kind, number_of_types, opening, closing)) {
			if (!check(kind, &current_element, is_opening)) return 2;
		}
		else if (symbol == ' ');
		else {
			return 1;
		}

		symbol = fgetc(stdin);
	}
	if (!empty(current_element)) return 2;
	return 0;
};

void push(int value, struct stack** current) {
	struct stack* head = (struct stack*)malloc(sizeof(struct stack));
	head->value = value;
	head->next = *current;
	*current = head;
};

int pop(struct stack** current_element) {
	if (empty(*current_element)) return 0;
	int value = (*current_element)->value;
	*current_element = (*current_element)->next;
	return value;
}




int main() {

	char string_of_brackets[max_lenght];

#define number_of_types 4
	char opening[number_of_types] = { '(', '[', '{', '<' };
	char closing[number_of_types] = { ')', ']', '}', '>' };

	int result_code = read(string_of_brackets, number_of_types, opening, closing);

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
	return 0;
}
