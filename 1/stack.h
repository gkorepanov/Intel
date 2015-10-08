#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
    SUGGETION: I'd better implement stack on array in this case.
           What's the reason to use list? If you have a lot of "push"s and "pop"s, 
           there will be many memory allocations and "free"s.
           You may use static array, if you anticipate certain number of element, or array with changing size.
           In last case, I mean something like c++'s <vector>. But in c you have to implement yourself.

           Nevetheless, on lectures Ilya Ded will tell you about stack on static array, as far as I know.
*/

/*
   It's not absolutely clear for me why using array here is better.
   1) Static array is not suitable: the sequence of brackets may be extremely large.
   2) Dynamic array as it implementes in <vector> means using realloc each time I do run out of memory. In other words, it is need that I have an empty memory area large enough each time I call realloc() and, moreover, it means copying all the values to a new cells of memory which is likely to have O(n) complexity.
   3) Using list is more effective to my mind (I do not state, just trying to understand).

Every time I push new element to stack, I need only sizeof(stack) bytes of available memory and I don't need to copy anything each time, as I had to using realloc(). You may object that I will get a 'distorted in memory' stack, i.e. there will be lots of stack's memory cells divided by lots of other cells, which makes processor work slower (according to your words). So we can just malloc memory with reservation for future pushes (just like in dynamic array), so that we could just put new elements to that allocated memory untill it is filled. Finally we would have few segments of memory, containing parts of stack, which is almoust equal to array, but more effective a bit (I believe so!).*/
  
typedef struct _stack {
    int value;
    struct _stack* next;
} stack;
void free_stack(stack** current_element);
void push(int value, stack** current);
int pop(stack** current_element);
bool is_empty(stack* current_element);
