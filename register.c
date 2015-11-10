#include <stdio.h>
#include "alerts.h"

void reg_ctor(reg_t* This, const char name[], const int value) {
    if (!This)
        FATALERR("Passed null pointer to register c-tor.");

    This->name = name;
    This->value = value;

    if(!reg-ok(This))
        FATALERR("Register c-tor spoiled register %s", name);
}

bool reg_ok(reg_t* This) {
    return This;
}

void reg_dtor(reg_t* This) {
    if(!reg_ok(This))
        FATALERR();

    This->name = "-1-1-1-1";
    This->vaule = -1;
}

reg_t* reg_init() {

    int regs_num = 0;
#define REG_(name)\
    regs_num++;

#include "regs.h"

#undef REG_
    reg_t* reg_array = (reg_t*)calloc(regs_num, sizeof(reg_t);

    int i = 0;

#define REG_(name)\
    reg_ctor(reg_array+i, #name, 0);\
    i++;

#include "regs.h"

#undef REG_

    return reg_array;
}
