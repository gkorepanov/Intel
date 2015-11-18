#define DEBUGMODE  1
#define MAX_NUM_OF_OPERANDS 2
#define MAX_WORD_LENGTH  30


#include "s_asm.h"

void to_begin(FILE* source) {
    fseek(source, 0, SEEK_SET);
}



bool is_lable(char str[]) {
    int len = strlen(str);

    return ((len>1) && (str[strlen(str)-1] == ':'));
}


int get_reg_num(char str[]) {
    int i = 0;
#define REG_(name, size, shift)\
    if (!strcmp(str, #name))\
        return i;\
    else\
        i++;\

#include "../s_common/s_reglist.h"

#undef REG_

    return -1;
}


bool get_line(line_t* line, char str[]) { // returns 0 if empty string or comment
    if (str[0] == '/') 
        return 0;

    char* token = strtok(str, "\n\r \t");

    DBGPRINT("Token: \"%s\"\n", token);

    if (!token)
        return 0;
    if (!strncmp(token, "//", 2))
        return 0;

    int i = 0;
    do {
        strcpy(line->words[i], token);
        i++;
        token = strtok(NULL, "\n\r \t");
        DBGPRINT("Token: \"%s\"\n", token);
    } while (token);

    line->num = i;
    DBGPRINT("String: %s Keyword: \"%s\"\n", str, line->words[0]);
    DBGPRINT("String \"%s\" transformed into line_t.\n", str);

    return 1;
}

bool load_function(FILE* source, vararray* lines) { //return 0 if no ret found
    DBGPRINT("Function found.\n");
    char str[200];
    line_t* cur_line = (line_t*)calloc(1, sizeof(line_t));

    while (fgets(str, 200, source)) {
        memset(cur_line, 0, sizeof(line_t));

        if (!get_line(cur_line, str))
            continue;

        var_push(lines, cur_line);

        if (!strcmp(cur_line->words[0], "ret"))
            return 1;
    }

    return 0;
}

void load_file(FILE* source, vararray* lines) {
    char str[200];
    line_t* cur_line = (line_t*)calloc(1, sizeof(line_t));
    vararray* func_code = var_ctor(sizeof(line_t), 128);

    DBGPRINT("Lines: %d\n", (int)(lines->nmax));

    while (fgets(str, 200, source)) {
        memset(cur_line, 0, sizeof(line_t));

        if (!get_line(cur_line, str))
            continue;

        if (!strcmp(cur_line->words[is_lable(cur_line->words[0])], "proc")) {
            var_push(func_code, cur_line);

            if(!load_function(source, func_code))
                USERERR("No ret from function found.");
                
        } 
        else {
            var_push(lines, cur_line);
        }

        DBGPRINT("Lines: %d\n", (int)(lines->nmax));
        DBGPRINT("String: %s\nKeyword: \"%s\"\n", str, cur_line->words[0]);
    }
    
    for (int i = 0; i < func_code->nmax; i++)
        var_push(lines, var_get(func_code, i));

    var_dtor(func_code);

}




int get_type(char str[]) {
    if (!strlen(str)) 
        return EMPTY;
    if (!strcmp(str, "proc")) 
        return FUNC;
    if (is_lable(str))
        return LABEL;

    return 0;
}

char get_modif(char str[]) {
    DBGPRINT("Got str: %s\n", str);

    if (get_reg_num(str) >= 0) 
        return 'r';

    for (int i = 0; i < strlen(str); i++)
        if (!isdigit(str[i]))
            return 'w';

    return 'n';
}

int get_digit(char str[]) {
    return atoi(str);
}


void put_lf(char str[], vararray* funcs, int shift) {
    func_t cur_func;
    strcpy(cur_func.name, str);
    cur_func.shift = shift;
    var_push(funcs, &cur_func);
    DBGPRINT("NAME: \"%s\", POS: %d;\n", str, shift);
}

int get_lf(char str[], vararray* funcs, int shift, int step) {
    DBGPRINT("NAME: \"%s\", shift of call/jump: %d\n", str, shift);

    for (int i = 0; i < (funcs->nmax); i++) {

        DBGPRINT("NAME: %s; SHIFT: %d\n",  ((func_t*)var_get(funcs, i))->name, (((func_t*)var_get(funcs, i))->shift-shift));
     
        if (!strcmp(str, ((func_t*)var_get(funcs, i))->name)) {
            return (((func_t*)var_get(funcs, i))->shift-shift);//QUESTION:why shift relates to another shift?
        }
    }

    if (step > 1)
        USERERR("No function/label found for %s\n", str);
}

int modif_cmp(char str1[], const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    

    if (len1!=len2)
        return 0;

    for (int i = 0; i < len1; i++) {
        if ((str1[i] == 'w') && ((str2[i] == 'l') || (str2[i] == 'f'))) 
            continue;
        else if (str1[i] != str2[i])
            return 0;
    }

    return 1;
}

void put_cmd(vararray* binary, line_t* cur_line, int j, vararray* labels, vararray* funcs, int step) {
    int i = j, argc = 0, to_push = 0, pos = 0;
    char cmd_num = 0;

    char* keyword = cur_line->words[j];
    char modif[4], words[2][MAX_WORD_LENGTH];
    memset(modif, 0, sizeof(modif));
    memset(words, 0, sizeof(words));

    for (i = j+1; i < cur_line->num; (argc++, i++)) {
        DBGPRINT("1/Argument %d: %s\n", 0, words[0]);//What's this debugoutput tell you?
        strcpy(words[argc], cur_line->words[i]);
        DBGPRINT("2/Argument %d: %s\n", 0, words[0]);
	DBGPRINT("Argument %d: %s\n", argc, words[argc]);//QUESTION: Why you repeat the same dbgoutput here
        modif[argc] = get_modif(words[argc]);
        DBGPRINT("Argument %d: %s\n", 0, words[0]);// and here?
    }

	DBGPRINT("Argument %d: %s\n", 0, words[0]);
    DBGPRINT("Pre-define: Number: %d, keyword: \"%s\" MODIF: \"%s\" argc: %d\n", cmd_num, keyword, modif, argc);

#define CMD_(number_, keyword_, argc_, modif_, code_)\
    if ((!strcmp(keyword, #keyword_)) && (modif_cmp(modif, modif_)) && (argc_ == argc)) {\
        strcpy(modif, modif_);\
        cmd_num = number_;\
    } else 

#include "../s_common/s_cmdlist.h"

#undef CMD_
    USERERR("No command found for \"%s\"\n", cur_line->words[0]);

   
    DBGPRINT("Number: %d, keyword: \"%s\" MODIF: \"%s\" argc: %d\n", cmd_num, keyword, modif, argc);
    pos = binary->nmax;//QUESTION: What's purpose of it?

    var_push(binary, &cmd_num);
    for (i = 0; i < argc; i++) {
        switch (modif[i]) {
            case 'r': {
                DBGPRINT("Call of get_reg_num.\n");
                to_push = get_reg_num(words[i]);
                break;
            }
            case 'n': {
                to_push = get_digit(words[i]);
                break;
            }
            case 'f': {
                to_push = get_lf(words[i], funcs, pos, step);
                break;
            }
            case 'l': {
                to_push = get_lf(words[i], labels, pos, step);
                break;
            }

            default: {
                FATALERR("Modif failure. Act_modif: %s\n", modif);//I think it's debug error. User shouldn't know it
                break;
            }
        }
        DBGPRINT("ARGUMENT %d: %d\n", i, to_push);
        var_pushn(binary, &to_push, sizeof(int));
    }

    DBGPRINT("Num of elems in bin: %d;\n"\
            "-----------------------------\n", (int)binary->nmax);
}

// step = 1 - no  control. step = 2 - if no label or func found, throw err
vararray* compile(vararray* lines, vararray* labels, vararray* funcs, int step) { 
    vararray* binary = var_ctor(sizeof(char), 128);

    int i = 0, j = 0; // i - line number; j - word number
    int type = 0;
    line_t* cur_line = NULL;
    char word[MAX_WORD_LENGTH];

    DBGPRINT("Lines: %d\n", (int)(lines->nmax));
    for (i = 0; i < (lines->nmax); i++) {
        j = 0;

        cur_line = (line_t*)var_get(lines, i);
                
        DBGPRINT("Label: %s\n", cur_line->words[j]);
        DBGPRINT("Next word: %s\n", cur_line->words[j+1]);
                
        DBGPRINT("Keyword: \"%s\"\n", cur_line->words[j]);
        type = get_type(cur_line->words[j]);
        DBGPRINT("Type: %d\n", type);

        if (type == FUNC) {
                put_lf(cur_line->words[j+1], funcs, binary->nmax);
                continue;
        }

        if (type == LABEL) {
                strcpy(word, cur_line->words[j]);
                word[strlen(word)-1] = '\0';
                put_lf(word, labels, binary->nmax);
                DBGPRINT("Label: %s\n", cur_line->words[j]);
                j++;
                DBGPRINT("Next word: %s\n", cur_line->words[j]);
                type = get_type(cur_line->words[j]);
        }

        if (type == EMPTY) 
            continue;

        put_cmd(binary, cur_line, j, labels, funcs, step);
    }
    if (step < 2) {
        var_dtor(binary);
        return NULL;
    }
    else 
        return binary;
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
    
    vararray* lines = var_ctor(sizeof(line_t), 128);
    vararray* labels = var_ctor(sizeof(label_t), 128);
    vararray* funcs = var_ctor(sizeof(func_t), 128);
    vararray* binary = var_ctor(sizeof(char), 128);

    load_file(source, lines);

    DBGPRINT("-------------------------------------------------------------\n"\
            "FILE LOADED.\n"\
            "--------------------------------------------------------------\n");

    compile(lines, labels, funcs, 1);
    
    DBGPRINT("-------------------------------------------------------------\n"\
            "FIRST COMPILATION RUNNED.\n"\
            "--------------------------------------------------------------\n");


    binary = compile(lines, labels, funcs, 2);

    DBGPRINT("-------------------------------------------------------------\n"\
            "SECOND COMPILATION RUNNED.\n"\
            "--------------------------------------------------------------\n");



    DBGPRINT("Size of binary: %d\n", (int) binary->nmax);

    fwrite(binary->mem, sizeof(char), binary->nmax, dest);

    var_dtor(binary);
    fclose(source);
    fclose(dest);

    return 0;
}
