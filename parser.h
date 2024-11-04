/****************************************
 * C-ploration 6 for CS 271
 * 
 * Patrick Punch
 * Fall 2024
 * 
 ****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

typedef int16_t hack_addr;
typedef int16_t opcode;

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH (MAX_LINE_LENGTH - 2)
/** function prototypes **/
char *strip(char *s);

void parse(FILE * file);

bool is_Atype(const char *);

bool is_label(const char *);

bool is_Ctype(const char *);

char *extract_label(const char *line, char *label);

enum instr_type
{
    INVALID_INSTR = -1,
    A_INSTR,
    C_INSTR
};

typedef struct c_instruction
{
    opcode a:1;
    opcode comp:6;
    opcode dest:3;
    opcode jmp:3;
} c_instruction;

typedef struct a_instruction
{
    union
    {
        hack_addr address;
        char *label;
    };
    bool is_addr;
} a_instruction;

typedef struct instruction
{
    union
    {
        a_instruction a_instr;
        c_instruction c_instr;
    };
    enum instr_type type;
} instruction;
