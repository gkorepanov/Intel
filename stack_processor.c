#include "alerts.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "stack_proc.h"

#define DEBUGMODE 1 //1 to print logs (alerts.h for implementation)


void proc_load(proc_t* This, FILE* source) {
    if (!proc_ok(This))
        FATALERR("Passed bad struct to loader.");
    
    int filesize = 0;
    
    fseek(source, 0, SEEK_END);
    filesize = ftell(source);

    DBGPRINT("Binary size: %d bytes.\n", filesize);
    
    This->size = filesize - 4;

    fseek(source, 4, SEEK_SET);

    This->cmds = (char*)realloc(This->cmds, This->size);
    fread(This->cmds, This->size, 1, source);

    if (DEBUGMODE) {
        FILE* debugfile = fopen("debug.stkex", "wb");
        fwrite(This->cmds, filesize-4, 1, debugfile);
        fclose(debugfile);
    }
}
void proc_ctor(proc_t* This) {
    if (!This) 
        FATALERR("Passed NULL pointer to proc c-tor");

    This->size = 0;
    This->pos = 0;
    This->cmds = (char*)calloc(10, sizeof(char));
    This->stack = (stack_t*)calloc(1, sizeof(stack_t));
    stack_ctor(This->stack);

    if (!proc_ok(This)) 
        FATALERR("Proc c-tor error");
}

void proc_dtor(proc_t* This) {
    if (!proc_ok(This)) 
        FATALERR("Proc d-tor got bad struct");

    free(This->cmds);
    stack_dtor(This->stack);
    free(This->stack);
    This->size = -1;
    This->pos = -1;
}

bool proc_ok(proc_t* This) {
    return This &&
        This->cmds &&
        (This->size >= 0) &&
        (This->pos >= 0) &&
        (This->pos <= This->size) &&
        This->stack &&
        stack_ok(This->stack);
}
    
void proc_run(proc_t* This) {
    if (!proc_ok(This)) 
        FATALERR("Passed bad struct to PROCESSOR.");

    printf("\nBEGIN\n");

    while ((This->cmds)[This->pos]) {
        switch((This->cmds)[This->pos]) {
#define CMD_(number, keyword, argc, code)\
            case number: {\
                if (DEBUGMODE) {\
                    printf("Command: %s", #keyword);\
                    if (argc)\
                        printf(" %d\n", *(int*)(This->cmds+This->pos+1));\
                    else\
                    printf("\n");\
                }\
                code;\
                This->pos += (1+argc*4);\
                break;\
            };

#include "stack_cmd.h"

#undef CMD_
            default:
                FATALERR("No command found. Pos: %d;"\
                         "Command number: %d\n", This->pos, (int)(This->cmds)[This->pos]);
        }
        
        if (!proc_ok(This))
            FATALERR("STRUCT proc corrupted while executing code\n"\
                     "Pos: %d Command number: %d\n", This->pos, (int)(This->cmds)[This->pos]);

        if (DEBUGMODE) 
            DBGPRINT("Pos: %d Command number: %d\n", This->pos, (int)(This->cmds)[This->pos]);
    }

    printf("END\n");
}



int main(int argc, char* argv[]) {
    if (argc < 2) 
        USERERR("USING: %s BINARY_FILE_NAME\n", argv[0]);

    printf("Executable: %s\n", argv[1]);

    FILE* source = fopen(argv[1], "rb");

    if (!source)
        USERERR("Can't open file \"%s\"\n", argv[1]);

    char check_file[5];
    fgets(check_file, 4+1, source);

    if (strcmp(check_file, "StPr"))
        USERERR("Source file is likely not a stack processor's binary"\
                "(found head bytes: \"%s\")\n", check_file);
        

    
    proc_t* proc = (proc_t*)calloc(1, sizeof(proc_t));
    proc_ctor(proc);
    proc_load(proc, source);
    proc_run(proc);
    proc_dtor(proc);

    fclose(source);
    return 0;
}
