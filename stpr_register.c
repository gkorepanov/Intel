#include <stdio.h>
#include "stpr_register.h"
#include <string.h>

int get_reg(char str[]) {
    int i;
#define REG_(name, size, shift)\
    if (!strcmp(str, #name))\
        return i;\
    else\
        i++;\

#include "stpr_reglist.h"

#undef REG_
    return 0;
}


