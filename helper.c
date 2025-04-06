#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

// Funcția care returnează tipul token-ului
TOKEN_TYPE token_type(char *token)
{
	if (strcmp(token, "if") == 0)
		return TOKEN_IF;
	else if (strcmp(token, "while") == 0)
		return TOKEN_WHILE;
	else if (strcmp(token, "for") == 0)
		return TOKEN_FOR;
	else if (strcmp(token, "a") == 0 || strcmp(token, "a;") == 0 ||
			 strcmp(token, "(a") == 0 || strcmp(token, "a)") == 0)
		return TOKEN_EAX;
	else if (strcmp(token, "b") == 0 || strcmp(token, "b;") == 0 ||
			 strcmp(token, "(b") == 0 || strcmp(token, "b)") == 0)
		return TOKEN_EBX;
	else if (strcmp(token, "c") == 0 || strcmp(token, "c;") == 0 ||
			 strcmp(token, "(c") == 0 || strcmp(token, "c)") == 0)
		return TOKEN_ECX;
	else if (strcmp(token, "d") == 0 || strcmp(token, "d;") == 0 ||
			 strcmp(token, "(d") == 0 || strcmp(token, "d)") == 0)
		return TOKEN_EDX;
	else if (strcmp(token, "+") == 0)
		return TOKEN_ADD;
	else if (strcmp(token, "MOV") == 0)
		return TOKEN_MOV;
	else if (strcmp(token, "&") == 0)
		return TOKEN_AND;
	else if (strcmp(token, "^") == 0)
		return TOKEN_XOR;
	else if (strcmp(token, "|") == 0)
		return TOKEN_OR;
	else if (strcmp(token, "-") == 0)
		return TOKEN_SUB;
	else if (strcmp(token, "*") == 0)
		return TOKEN_MUL;
	else if (strcmp(token, "/") == 0)
		return TOKEN_DIV;
	else if (strcmp(token, ">>") == 0)
		return TOKEN_SHR;
	else if (strcmp(token, "<<") == 0)
		return TOKEN_SHL;
	else if (strcmp(token, "CMP") == 0)
		return TOKEN_CMP;
	else if (strcmp(token, "JMP") == 0)
		return TOKEN_JMP;
	else if (strcmp(token, "==") == 0)
		return TOKEN_JNE;
	else if (strcmp(token, "!=") == 0)
		return TOKEN_JE;
	else if (strcmp(token, ">") == 0)
		return TOKEN_JLE;
	else if (strcmp(token, ">=") == 0)
		return TOKEN_JL;
	else if (strcmp(token, "<") == 0)
		return TOKEN_JGE;
	else if (strcmp(token, "<=") == 0)
		return TOKEN_JG;
	else if (strcmp(token, "}") == 0)
		return TOKEN_END;
	else
		return TOKEN_DEFAULT;
}

// Funcția care returnează string-ul corespunzător token-ului
char *token_type_2_string(char *token)
{
	switch (token_type(token))
	{
	case TOKEN_IF:
		return "if";
	case TOKEN_WHILE:
		return "while";
	case TOKEN_FOR:
		return "for";
	case TOKEN_EAX:
		return "eax";
	case TOKEN_EBX:
		return "ebx";
	case TOKEN_ECX:
		return "ecx";
	case TOKEN_EDX:
		return "edx";
	case TOKEN_MOV:
		return "MOV";
	case TOKEN_ADD:
		return "ADD";
	case TOKEN_AND:
		return "AND";
	case TOKEN_XOR:
		return "XOR";
	case TOKEN_OR:
		return "OR";
	case TOKEN_SUB:
		return "SUB";
	case TOKEN_MUL:
		return "MUL";
	case TOKEN_DIV:
		return "DIV";
	case TOKEN_SHR:
		return "SHR";
	case TOKEN_SHL:
		return "SHL";
	case TOKEN_CMP:
		return "CMP";
	case TOKEN_JMP:
		return "JMP";
	case TOKEN_JE:
		return "JE";
	case TOKEN_JNE:
		return "JNE";
	case TOKEN_JG:
		return "JG";
	case TOKEN_JGE:
		return "JGE";
	case TOKEN_JL:
		return "JL";
	case TOKEN_JLE:
		return "JLE";
	case TOKEN_DEFAULT:
		return "DEFAULT";
	default:
		return "UNKNOWN";
	}
}

// Print-ează funcția corespunzătoare token-ului și argumentele acesteia
void print_func(char *func, char *arg1, char *arg2)
{
	if (token_type(arg2) == TOKEN_DEFAULT) // Verific dacă arg2 este registru
	{
		printf("%s %s, ", token_type_2_string(func), token_type_2_string(arg1));
		for (size_t i = 0; i < strlen(arg2); i++)
		{
			if (arg2[i] == ';' || arg2[i] == ')')
				break;

			printf("%c", arg2[i]);
		}
		printf("\n");
	} else {
		printf("%s %s, %s\n", token_type_2_string(func),
			   token_type_2_string(arg1), token_type_2_string(arg2));
	}
}

// Funcția care se ocupă de funcțiile de tip simbol
void symbol_func(char **tokens)
{
	if (token_type(tokens[3]) != TOKEN_MUL && token_type(tokens[3]) != TOKEN_DIV) {
		print_func(tokens[3], tokens[0], tokens[4]);
	} else {
		if (token_type(tokens[3]) == TOKEN_MUL)
		{
			if (token_type(tokens[0]) == TOKEN_EAX)
			{
				if (token_type(tokens[4]) == TOKEN_DEFAULT) {
					printf("MUL ");
					for (size_t i = 0; i < strlen(tokens[4]); i++)
					{
						if (tokens[4][i] == ';')
							break;

						printf("%c", tokens[4][i]);
					}
					printf("\n");
				} else {
					printf("MUL %s\n", token_type_2_string(tokens[4]));
				}
			} else {
				printf("MOV eax, %s\n", token_type_2_string(tokens[0]));
				if (token_type(tokens[4]) == TOKEN_DEFAULT) {
					printf("MUL ");
					for (size_t i = 0; i < strlen(tokens[4]); i++)
					{
						if (tokens[4][i] == ';')
							break;

						printf("%c", tokens[4][i]);
					}
					printf("\n");
				} else {
					printf("MUL %s\n", token_type_2_string(tokens[4]));
				}
				printf("MOV %s, eax\n", token_type_2_string(tokens[0]));
			}
		} else {
			if (strcmp(tokens[4], "0;") == 0) {
				printf("Error\n");
				return;
			}
			if (token_type(tokens[0]) == TOKEN_EAX) {
				if (token_type(tokens[4]) == TOKEN_DEFAULT) {
					printf("DIV ");
					for (size_t i = 0; i < strlen(tokens[4]); i++)
					{
						if (tokens[4][i] == ';')
							break;

						printf("%c", tokens[4][i]);
					}
					printf("\n");
				} else {
					printf("DIV %s\n", token_type_2_string(tokens[4]));
				}
			} else {
				printf("MOV eax, %s\n", token_type_2_string(tokens[0]));
				if (token_type(tokens[4]) == TOKEN_DEFAULT) {
					printf("DIV ");
					for (size_t i = 0; i < strlen(tokens[4]); i++)
					{
						if (tokens[4][i] == ';')
							break;
						printf("%c", tokens[4][i]);
					}
					printf("\n");
				} else {
					printf("DIV %s\n", token_type_2_string(tokens[4]));
				}
				printf("MOV %s, eax\n", token_type_2_string(tokens[0]));
			}
		}
	}
}

// Funcția care se ocupă de conversia din C în ASM
void c_to_asm(char *line, int *token_flag, char *for_register)
{
	char **tokens = NULL;
	int token_count = 0;
	char *token = strtok(line, " \t\n;"); // Împarte linia in tokens
	while (token)
	{
		tokens = realloc(tokens, sizeof(char *) * (token_count + 1));
		if (!tokens)
		{
			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
		tokens[token_count] = malloc(strlen(token) + 1);
		if (!tokens[token_count])
		{
			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
		strcpy(tokens[token_count], token); // Copiază token-ul în memorie
		token_count++;
		token = strtok(NULL, " \t\n"); // Continuă despărțirea
	}

	// Verifică dacă avem o instrucțiune de tip if, while sau for
	// și apelează funcția corespunzătoare pentru fiecare caz.
	// Dacă nu avem o instrucțiune mai sus aminitită atunci
	// se va apela funcția care se ocupă de simboluri
	switch (token_type(tokens[0]))
	{
	case TOKEN_IF:
		*token_flag = 1;
		print_func("CMP", tokens[1], tokens[3]);
		printf("%s end_label\n", token_type_2_string(tokens[2]));
		break;
	case TOKEN_WHILE:
		*token_flag = 2;
		printf("start_loop:\n");
		print_func("CMP", tokens[1], tokens[3]);
		printf("%s end_label\n", token_type_2_string(tokens[2]));
		break;
	case TOKEN_FOR:
		*token_flag = 3;
		strcpy(for_register, tokens[1]); // Salvează registrul pentru for
		print_func("MOV", tokens[1], tokens[3]);
		printf("start_loop:\n");
		print_func("CMP", tokens[4], tokens[6]);
		printf("%s end_label\n", token_type_2_string(tokens[5]));
		break;
	case TOKEN_END:
		if (*token_flag == 1)
		{
			printf("end_label:\n");
			*token_flag = 0;
		} else if (*token_flag == 2) {
			printf("JMP start_loop\n");
			printf("end_label:\n");
			*token_flag = 0;
		} else if (*token_flag == 3) {
			print_func("+", for_register, "1");
			printf("JMP start_loop\n");
			printf("end_loop:\n");
			*token_flag = 0;
		}
		break;
	default:
		// Verificăm dacă instrucțiunea este o simplă atribuire
		// dacă da atunci se va apela funcția print_func cu MOV ca funcție
		// iar dacă nu se va apela symbol_func
		if (strcmp(tokens[0], tokens[2]) != 0)
		{
			print_func("MOV", tokens[0], tokens[2]);
			break;
		}
		symbol_func(tokens);
		break;
	}
	free(tokens);    // Eliberează memoria pentru lista de token-uri
	tokens = NULL;   // Resetează pointerul
	token_count = 0; // Resetează numărul de token-uri
}
