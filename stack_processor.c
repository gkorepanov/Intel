#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "USING: %s BINARY_FILE_NAME\n", argv[0]);
        return 1;
    }

    printf("Binary: %s\n", argv[1]);

    FILE* source = fopen(argv[1], "rb");

    if (!source) {
        fprintf(stderr, "Incorrect file name\n");
        return 1;
    }

    char check_file[5];
    fgets(check_file, 4+1, source);

    if (strcmp(check_file, "StPr")) {
        fprintf(stderr, "Source file is likely not a stack processor's binary (found head bytes: \"%s\"\n", check_file);
        return 1;
    }


    unsigned char cmd_num = 0;
    int operands[10];
    int operands_num = 0;

    stack_t main_stack = {0, NULL};
    stack_ctor(&main_stack);

    fread(&cmd_num, 1, sizeof(unsigned char), source);

    while (!feof(source)) {
        
        switch(cmd_num) {
#define CMD_(number, keyword, argc, code)\
            case number: {code; printf("Command: %s %d\n", #keyword, argc?operands[0]:-1); break;}\

#include "stack_cmd.h"

#undef CMD_
            default:
                assert(0 && "Fatal error. No command found");
        }

        stack_dump(&main_stack);
        fread(&cmd_num, 1, sizeof(unsigned char), source);
    }


    fclose(source);

    return 0;
}
