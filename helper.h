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
	TOKEN_EAX,
	TOKEN_EBX,
	TOKEN_ECX,
	TOKEN_EDX,
	TOKEN_MOV,
	TOKEN_ADD,
	TOKEN_AND,
	TOKEN_XOR,
	TOKEN_OR,
	TOKEN_SUB,
	TOKEN_MUL,
	TOKEN_DIV,
	TOKEN_SHR,
	TOKEN_SHL,
	TOKEN_CMP,
	TOKEN_JMP,
	TOKEN_JE,
	TOKEN_JNE,
	TOKEN_JG,
	TOKEN_JGE,
	TOKEN_JL,
	TOKEN_JLE,
	TOKEN_END,
	TOKEN_DEFAULT
} TOKEN_TYPE; // Enum pentru tipurile de tokenuri

TOKEN_TYPE token_type(char *token);
char *token_type_2_string(char *token);
void print_func(char *func, char *arg1, char *arg2);
void symbol_func(char **tokens);
void c_to_asm(char *line, int *token_flag, char *for_register);

#endif
