#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

int strtoi_(char* source) {
    int result = 0;
    while (*source) {
        if (!isdigit(*source)) {
                fprintf(stderr, "Error while reading operand (symbol code is \"%d\".", *source);
                assert(0);
        }
        result *= 10;
        result += ((*source) - '0');
        source++;
    }
    
    return result;
}

void parse_string(unsigned char* cmd_num, char* cur_str, int* operands_num, int* operands) {
    printf("Got string: \"%s\"\n", cur_str);

    char* copy_str = (char*)calloc(strlen(cur_str), sizeof(char));
    memcpy(copy_str, cur_str, strlen(cur_str));

    printf("Copied to: \"%s\"\n", copy_str);

    char* word = strsep(&copy_str, " \n\t\r");
    printf("Keyword: %s\n", word);

    *cmd_num = -1;

#define CMD_(number, keyword, argc, code)\
    if (!strcmp(word, #keyword)) {\
        *cmd_num = number;\
        *operands_num = argc;\
    } else\

#include "stack_cmd.h"

#undef CMD_
    {
        fprintf(stderr, "Error reading keyword in string \"%s\"\n", cur_str);
        fflush(stderr);
        assert(0);
    }
    
    printf("Number: %d; operands: %d;\n", *cmd_num, *operands_num);


    int i = 0, operand = 0;
    for(i = 0; i < *operands_num; i++) {
        printf("Parsing operand: %s;\n", copy_str);
        operand = strtoi_(strsep(&copy_str, " \n\t\r"));
        operands[i] = operand;
        printf("Operand: %d;\n", operand);
    }

}

void put_string(unsigned char cmd_num, int operands_num, int* operands, FILE* dest) {
    printf("Number: %d; operands: %d;\n", cmd_num, operands[0]);
    fwrite(&cmd_num, sizeof(unsigned char), 1, dest);
    fwrite(operands, sizeof(int), operands_num, dest);
    printf("Written command.\n");
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "USING: stack_compiler SOURCE_FILE_NAME OUTPUT_FILE_NAME\n");
        return 0;
    }

    printf("Source: %s; Binary: %s\n", argv[1], argv[2]);

    FILE* source = fopen(argv[1], "r");
    FILE* dest = fopen(argv[2], "wb");

    if ((!source)||(!dest)) {
        fprintf(stderr, "Incorrect file name\n");
        return 0;
    }

    char cur_str[100];
    unsigned char cmd_num = 0;
    int operands[10];
    int operands_num = 0;
    
    fputs("StPr", dest);

    while (fgets(cur_str, 100, source)) {
        printf("Read \"%s\"\n", cur_str);
        parse_string(&cmd_num, cur_str, &operands_num, operands);
        printf("Parsed.\n");
        put_string(cmd_num, operands_num, operands, dest);
    }
    
    fclose(source);
    fclose(dest);

    return 0;
}

