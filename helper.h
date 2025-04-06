#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024 // Dimensiunea maximă a liniei

typedef enum
{
    TOKEN_IF,
    TOKEN_WHILE,
    TOKEN_FOR,
    EAX,
    EBX,
    ECX,
    EDX,
    MOV,
    ADD,
    AND,
    XOR,
    OR,
    SUB,
    MUL,
    DIV,
    SHR,
    SHL,
    CMP,
    JMP,
    JE,
    JNE,
    JG,
    JGE,
    JL,
    JLE,
    END,
    TOKEN_DEFAULT
} TOKEN_TYPE; // Enum pentru tipurile de tokenuri

TOKEN_TYPE token_type(char *token);
char *token_type_2_string(char *token);
void print_func(char *func, char *arg1, char *arg2);
void symbol_func(char **tokens);
void c_to_asm(char *line, int *token_flag, char *for_register);

#endif // HELPER_H