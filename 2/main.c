#include "_string.h"
#include <stdlib.h>
#include <stdio.h>

main() { // for check
    char string[10];
    char* string_from_num;
    int num;

    scanf("%s%i", string, &num);
    string_from_num = _itoa(num);
    printf("%i\n%s\n", _atoi(string), string_from_num);
    free(string_from_num);
    return 0;
};

