#include "_string.h"
#include <stdlib.h>
#include <stdio.h>

main() { // for check
    char string[10];
    int num;
    scanf("%s%i", string, &num);
    printf("%i\n%s\n", _atoi(string), _itoa(num));
    return 0;
};

