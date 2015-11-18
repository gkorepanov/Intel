#include "s_proc.h"

#define DEBUGMODE 0 //1 to print logs (alerts.h for implementation)


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
    This->stack_ret = (stack_t*)calloc(1, sizeof(stack_t));

    stack_ctor(This->stack);
    stack_ctor(This->stack_ret);

    This->regs = reg_init();

    if (!proc_ok(This)) 
        FATALERR("Proc c-tor error");
}

void proc_dtor(proc_t* This) {
    if (!proc_ok(This)) 
        FATALERR("Proc d-tor got bad struct");

    free(This->cmds);

    stack_dtor(This->stack);
    stack_dtor(This->stack_ret);

    free(This->stack);
    free(This->stack_ret);
    
    reg_free(This->regs);


    This->size = -1;
    This->pos = -1;
}

bool proc_ok(proc_t* This) {
    return This &&
        This->cmds &&
        This->regs &&
        (This->size >= 0) &&
        (This->pos >= 0) &&
        (This->pos <= This->size) &&
        This->stack &&
        This->stack_ret &&
        stack_ok(This->stack) &&
        stack_ok(This->stack_ret);
}
    
void proc_run(proc_t* This) {
    if (!proc_ok(This)) 
        FATALERR("Passed bad struct to PROCESSOR.");

    printf("\nBEGIN\n");

    while ((This->cmds)[This->pos]) {
        switch((This->cmds)[This->pos]) {
#define CMD_(number, keyword, argc, modif, code)\
            case number: {\
                if (DEBUGMODE) {\
                    int j = argc;\
                    printf("-------------------------------------------------------------\n"\
                            "Pos: %d\nCommand: %s(%d)", This->pos, #keyword, number);\
                    while (j) {\
                        printf(" %d", *(int*)(This->cmds+This->pos+1+(argc-j)*4));\
                        j--;\
                    }\
                    printf("\n");\
                    getchar();\
                }\
                code;\
                This->pos += (1+argc*4);\
                break;\
            };

#include "../s_common/s_cmdlist.h"

#undef CMD_
            default:
                FATALERR("No command found. Pos: %d;"\
                         "Command number: %d\n", This->pos, (int)(This->cmds)[This->pos]);
        }
        
        if (!proc_ok(This))
            FATALERR("STRUCT proc corrupted while executing code\n"\
                     "Pos: %d Command number: %d\n", This->pos, (int)(This->cmds)[This->pos]);

            DBGPRINT("Done.\n");
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
    
    DBGPRINT("Passed all.\n");

    fclose(source);
    return 0;
}
