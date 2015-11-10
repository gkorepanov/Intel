#ifndef REG
#define REG

typedef struct {
    char name[10];
    int value;
} reg_t;

bool reg_ok(reg_t* This);
void reg_ctor(reg_t* This);
void reg_dtor(reg_t* This);
void reg_init(reg_t* reg_array);

#endif
