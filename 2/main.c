#include "_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() { // testing
    printf("Testing itoa and atoi functions:\n\n");

    char str[10], str2[10];
    
    for (int i = -32000; i < 32000; i += 87) {
        sprintf(str, "%d", i);
        _itoa(i, str2);
        if (strcmp(str, str2)) {
                fprintf(stderr, "Error while passing number %d in function itoa!\n", i);
                return 0;
            }
    }

    printf("Function itoa tested!\n");

    for (int i = -32000; i < 32000; i += 87) {
        sprintf(str, "%d", i);
        if (atoi(str) - i) {
                fprintf(stderr, "Error while passing number %d in function atoi!\n", i);
                return 0;
        }
    }

    printf("Function atoi tested!\n");

    return 0;
};

