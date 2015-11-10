/* 
SOURCE structure:
----------------------------------------
push ax
mov 45 cx
pop
...
operator|operand 1|operand 2|operand 3
----------------------------------------




BINARY structure:
-----------------------------------------------------------------------------------
0 2 1
11 1 45 2 3
5
...
command (char number)|type of operand 1 (char number)|operand 1 (int number)| ...
-----------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "operands.h"
#include "alerts.h"

#define DEBUGMODE = 1
#define MAX_NUM_OF_OPERANDS 2

typedef struct {
    char name[30];
    int shift;
} label_t;

void to_begin(FILE* source) {
    fseek(source, 0, SEEK_SET);
}

void make_binary(FILE* source, FILE* dest) {
    to_begin(source);
    
    label_t labels[500];
    
initialize labels

    char cur_str[100];
    int cmd_type = 0;

    char words[4][30];


    while(fgets...) {
        get_parts(cur_str, words);

        cmd_type = get_type(words[0]);

        switch(cmd_type) {
            case OPERATION:
                //using stack_cmd.h

            case LABEL:

        }
    

    


int main(int argc, char* argv[]) {
    if (argc < 3) 
        USERERR("USING: %s SOURCE_FILE_NAME OUTPUT_FILE_NAME\n", argv[0]);

    printf("Source: %s; Executable: %s\n", argv[1], argv[2]);

    FILE* source = fopen(argv[1], "r");
    FILE* dest = fopen(argv[2], "wb");

    if (!source)
        USERERR("Can't open file \"%s\"n", argv[1]);

    if (!dest)
        USERERR("Can't create file \"%s\"\n", argv[2]);
    
    fputs("StPr", dest);
    
    make_binary(source, dest);

    fclose(source);
    fclose(dest);

    return 0;
}

