typedef int value_t; // for any type support

typedef struct _elem {
    value_t value;
    struct _elem* next;
} elem_t;

typedef struct {
    int size;
    elem_t* head;
} stack_t;

void elem_ctor(elem_t* This);
void elem_dtor(elem_t* This);
int elem_ok(elem_t* This);

void stack_ctor(stack_t* This);
void stack_dtor(stack_t* This);
int stack_ok(stack_t* This);

void stack_push(stack_t* This, value_t value);
int stack_pop(stack_t* This); // returns 0 if succeed 
value_t stack_top(stack_t* This);
int is_empty(stack_t* This);

void stack_dump(stack_t* This);
void elem_dump(elem_t* This);
