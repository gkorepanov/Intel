#ifndef STCOMPILE
#define STCOMPILE

typedef struct {
    char name[30];
    int shift;
} label_t, func_t;

typedef struct {
    char words[4][MAX_WORD_LENGTH];
    int num;
} line_t;

enum {
    LABEL = 1,
    FUNC = 2,
    EMPTY = 3
};

enum {
    REGISTER = 1,
    NUMBER = 2,
    WORD = 3
};

bool is_lable(char str[]);
bool get_line(line_t* line, char str[]);
bool load_function(FILE* source, vararray* lines);
void load_file(FILE* source, vararray* lines);
int get_type(char str[]);
char get_modif(char arg[]);
int get_digit(char str[]);
void put_lf(char str[], vararray* funcs, int shift);
int get_lf(char str[], vararray* funcs, int shift, int step);
void put_cmd(vararray* binary, line_t* cur_line, int j, vararray* labels, vararray* funcs, int step);
vararray* compile(vararray* lines, vararray* labels, vararray* funcs, int step);

#endif
