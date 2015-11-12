#ifndef PROC
#define PROC

typedef struct {
    char* cmds;
    int size;
    int pos;
    stack_t* stack;
} proc_t;

void proc_load(proc_t* This, FILE* source);
void proc_ctor(proc_t* This);
void proc_dtor(proc_t* This);
bool proc_ok(proc_t* This);
void proc_run(proc_t* This, FILE* source);

#endif
