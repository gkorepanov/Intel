#ifndef LIST
#define LIST

typedef int bool;
#define true 1
#define false 0

typedef struct _list {
    int value;
    struct _list* next;
} list_t;

void list_ctor(list_t* This, int value, list_t* next);
void list_dtor(list_t* This);

void list_put(list_t* This, int value);
int list_get(list_t* This);
void list_rm(list_t* This);

bool list_ok(list_t* This);
void list_dump(list_t* This);

#endif
