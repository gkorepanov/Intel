#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s_register.h"

reg_t* reg_init() {
    reg_t* regs = (reg_t*)calloc(1, sizeof(reg_t));
    regs->shifts = (int*)calloc(REG_NUM, sizeof(int));
    
    regs->sizes = (int*)calloc(REG_NUM, sizeof(int));
    
    int i = 0, size = 0;
#define REG_(name, size, shift)\
    regs->sizes[i] = size;\
    regs->shifts[i] = shift;\
    i++;

#include "../s_common/s_reglist.h"

#undef REG_

    for (i = 0; i < REG_NUM; i++) {
        if ((regs->shifts[i]+regs->sizes[i]) > size)
            size = regs->shifts[i]+regs->sizes[i];
    }

    regs->mem = (char*)calloc(size, 1);
    memset(regs->flags, 0, sizeof(regs->flags));
    return regs;
}

void reg_put(int number, int value, reg_t* regs) {
    memcpy(regs->mem+regs->shifts[number], &value, regs->sizes[number]);
}

int reg_get(int number, reg_t* regs) {
    int result = 0;
    memcpy(&result, regs->mem+regs->shifts[number], regs->sizes[number]);
    return result;
}

void reg_free(reg_t* regs) {
    free(regs->sizes);
    free(regs->shifts);
    free(regs->mem);
    free(regs);
}
