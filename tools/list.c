#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include <assert.h>

void list_ctor(list_t* This, int value, list_t* next) {
    assert(This);

    This->value = value;
    This->next = next;

    assert(list_ok(This));
}

void list_dtor(list_t* This) {
    assert(list_ok(This));

    list_t* temp;

    while (This) {
        assert(list_ok(This));
        temp = This;
        This = This->next;
        temp->value = -1;
        temp->next = NULL;
        free(temp);
    }
}

void list_put(list_t* This, int value) {
    assert(list_ok(This));

    list_t* new_ = (list_t*)calloc(1, sizeof(list_t));
    list_ctor(new_, This->value, This->next);
    This->next = new_;
    This->value = value;
    assert(list_ok(This));
}



int list_get(list_t* This) {
    assert(list_ok(This));
    
    return This->value;
}

void list_rm(list_t* This) {
    assert(list_ok(This));

    list_t* temp = This->next;
    This->value = This->next->value;
    This->next = This->next->next;
    temp->value = -1;
    temp->next = NULL;
    free(temp);

    assert(list_ok(This));
}

bool list_ok(list_t* This) {
    return (This);
}

void list_dump(list_t* This) {
    assert(list_ok(This));
    printf("elements: ");

    while (This->next) {
        assert(list_ok(This));
        printf("%d ", This->value);
        This = This->next;
    }
    printf("\n");
}
