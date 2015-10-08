#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include <ctype.h>

int check(int kind, stack** current_element, int is_opening);
int is_bracket(char symbol, int* is_opening, int* kind, int NUMBER_OF_TYPES, char* opening, char*  closing);
int read(int NUMBER_OF_TYPES, char* opening, char*  closing); // 0 - right 1 - error 2 - wrong; had to leave reading from input here for one-by-one input
void print_result(int result_code);
char get_symbol(); // '\n' MUST be a sign of the end of the brackets sequence

int is_bracket(char symbol, int* is_opening, int* kind, int number_of_types, char* opening, char*  closing) {
    int i;
    for (i = 0; i < number_of_types; i++) {
        if (opening[i] == symbol) {
            *is_opening = 1;
            *kind = i; 
            return 1; 
        }
        else if (closing[i] == symbol) {
            *is_opening = 0;
            *kind = i;
            return 1;
        }
    }
    return 0;
};



int check(int kind, stack** current_element, int is_opening) {
    if (is_opening) {
        push(kind, current_element);
        return 1;
    }
    if (is_empty(*current_element)) return 0;
    int compared = pop(current_element);
    if (compared == kind) return 1;
    return 0;
};

char get_symbol() { // '\n' must be a sign of the end of the brackets sequence
    return fgetc(stdin);
};

int is_allowed_symbol(char symbol) {
    if (isdigit(symbol)) return 1;
#define NUMBER_OF_SYMBOLS 10
    char allowed_symbols[NUMBER_OF_SYMBOLS] = {'*', '/', '-', '+', ' ', '<', '>', '^', '=', '%'};
    for (int i = 0; i < NUMBER_OF_SYMBOLS; i++) {
        if (symbol == allowed_symbols[i]) 
            return 1;
    }

    return 0;
};

int read(int number_of_types, char* opening, char*  closing) {
    char symbol = 0;
    int is_opening = 0;
    int kind = 0;
    stack* current_element = NULL;// TODO. It's very dangerous to use NULL. Moreover you don't check anywhere.
                                  // Implement init(), it's like constructor in c++
    symbol = get_symbol();

    while (symbol != '\n') {
        if (is_bracket(symbol, &is_opening, &kind, number_of_types, opening, closing)) {
            if (!check(kind, &current_element, is_opening)) return 2;
        }
        else if (!is_allowed_symbol(symbol)) return 1 ;
        
        symbol = get_symbol();
    }
    if (!is_empty(current_element)) {
        free_stack(&current_element);
        return 2;
    }
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
                fprintf(stderr, "Unfortunately, you've typed wrong sequence of brackets.\n");
                break;
    }
    }
};

int main() {
#define NUMBER_OF_TYPES 4
    char opening[NUMBER_OF_TYPES] = { '(', '[', '{', '<' };
    char closing[NUMBER_OF_TYPES] = { ')', ']', '}', '>' };
    int result_code = read(NUMBER_OF_TYPES, opening, closing);
    print_result(result_code);
    return 0;
};
