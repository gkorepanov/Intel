#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../tools/s_alerts.h"
#include "../tools/stack.h"
#include "s_register.h"

#ifndef S_PROC
#define S_PROC

typedef struct {
    char* cmds;
    int size;
    int pos;
    stack_t* stack;
    stack_t* stack_ret;
    reg_t* regs;
} proc_t;

void proc_load(proc_t* This, FILE* source);
void proc_ctor(proc_t* This);
void proc_dtor(proc_t* This);
bool proc_ok(proc_t* This);
void proc_run(proc_t* This, FILE* source);

#endif
