#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

TOKEN_TYPE token_type(char *token)
{
    if (strcmp(token, "if") == 0)
        return TOKEN_IF;
    else if (strcmp(token, "while") == 0)
        return TOKEN_WHILE;
    else if (strcmp(token, "for") == 0)
        return TOKEN_FOR;
    else if (strcmp(token, "a") == 0 || strcmp(token, "a;") == 0 || strcmp(token, "(a") == 0 || strcmp(token, "a)") == 0)
        return EAX;
    else if (strcmp(token, "b") == 0 || strcmp(token, "b;") == 0 || strcmp(token, "(b") == 0 || strcmp(token, "b)") == 0)
        return EBX;
    else if (strcmp(token, "c") == 0 || strcmp(token, "c;") == 0 || strcmp(token, "(c") == 0 || strcmp(token, "c)") == 0)
        return ECX;
    else if (strcmp(token, "d") == 0 || strcmp(token, "d;") == 0 || strcmp(token, "(d") == 0 || strcmp(token, "d)") == 0)
        return EDX;
    else if (strcmp(token, "+") == 0)
        return ADD;
    else if (strcmp(token, "MOV") == 0)
        return MOV;
    else if (strcmp(token, "&") == 0)
        return AND;
    else if (strcmp(token, "^") == 0)
        return XOR;
    else if (strcmp(token, "|") == 0)
        return OR;
    else if (strcmp(token, "-") == 0)
        return SUB;
    else if (strcmp(token, "*") == 0)
        return MUL;
    else if (strcmp(token, "/") == 0)
        return DIV;
    else if (strcmp(token, ">>") == 0)
        return SHR;
    else if (strcmp(token, "<<") == 0)
        return SHL;
    else if (strcmp(token, "CMP") == 0)
        return CMP;
    else if (strcmp(token, "JMP") == 0)
        return JMP;
    else if (strcmp(token, "==") == 0)
        return JNE;
    else if (strcmp(token, "!=") == 0)
        return JE;
    else if (strcmp(token, ">") == 0)
        return JLE;
    else if (strcmp(token, ">=") == 0)
        return JL;
    else if (strcmp(token, "<") == 0)
        return JGE;
    else if (strcmp(token, "<=") == 0)
        return JG;
    else if (strcmp(token, "}") == 0)
        return END;
    else
        return TOKEN_DEFAULT;
} // Funcția care returnează tipul token-ului

char *token_type_2_string(char *token)
{
    switch (token_type(token))
    {
    case TOKEN_IF:
        return "if";
    case TOKEN_WHILE:
        return "while";
        break;
    case TOKEN_FOR:
        return "for";
        break;
    case EAX:
        return "EAX";
        break;
    case EBX:
        return "EBX";
        break;
    case ECX:
        return "ECX";
        break;
    case EDX:
        return "EDX";
        break;
    case MOV:
        return "MOV";
        break;
    case ADD:
        return "ADD";
        break;
    case AND:
        return "AND";
        break;
    case XOR:
        return "XOR";
        break;
    case OR:
        return "OR";
        break;
    case SUB:
        return "SUB";
        break;
    case MUL:
        return "MUL";
        break;
    case DIV:
        return "DIV";
        break;
    case SHR:
        return "SHR";
        break;
    case SHL:
        return "SHL";
        break;
    case CMP:
        return "CMP";
        break;
    case JMP:
        return "JMP";
        break;
    case JE:
        return "JE";
        break;
    case JNE:
        return "JNE";
        break;
    case JG:
        return "JG";
        break;
    case JGE:
        return "JGE";
        break;
    case JL:
        return "JL";
        break;
    case JLE:
        return "JLE";
        break;
    case TOKEN_DEFAULT:
        return "DEFAULT";
        break;
    default:
        break;
    }
} // Funcția care returnează string-ul corespunzător token-ului

// Funcția care print-ează funcția corespunzătoare tipului de token și argumentele acesteia
void print_func(char *func, char *arg1, char *arg2)
{
    if (token_type(arg2) == TOKEN_DEFAULT) // Dacă arg2 nu este un registru afisez câte un char până ajung la ';'
    {
        printf("%s %s, ", token_type_2_string(func), token_type_2_string(arg1));
        for (int i = 0; i < strlen(arg2); i++)
        {
            if (arg2[i] == ';')
            {
                break;
            }
            else
            {
                printf("%c", arg2[i]);
            }
        }
        printf("\n");
    }
    else
    {
        printf("%s %s, %s\n", token_type_2_string(func),
               token_type_2_string(arg1), token_type_2_string(arg2));
    }
}

// Funcția care se ocupă de funcțiile de tip simbol
void symbol_func(char **tokens)
{
    // Dacă token-ul ce reprezintă operatorul funcției nu este MUL sau DIV
    // atunci se va apela funcția print_func cu argumentele corespunzătoare
    if (token_type(tokens[3]) != MUL && token_type(tokens[3]) != DIV)
    {
        print_func(tokens[3], tokens[0], tokens[4]);
    }
    else
    {
        // Dacă token-ul reprezintă operatorul MUL
        // atunci facem logica din spate pentru acest operator
        if (token_type(tokens[3]) == MUL)
        {
            // Dacă token-ul ce reprezintă locația rezultatului inmulțirii nu este EAX
            // atunci se va face un MOV în EAX cu token-ul ce reprezintă primul operand
            // iar apoi se va face un MUL cu token-ul ce reprezintă al doilea operand
            // iar rezultatul se va muta în token-ul ce reprezintă primul operand
            if (token_type(tokens[0]) == EAX)
            {
                if (token_type(tokens[4]) == TOKEN_DEFAULT)
                {
                    printf("MUL ");
                    for (int i = 0; i < strlen(tokens[4]); i++)
                    {
                        if (tokens[4][i] == ';')
                        {
                            break;
                        }
                        else
                        {
                            printf("%c", tokens[4][i]);
                        }
                    }
                    printf("\n");
                }
                else
                {
                    printf("MUL %s\n", token_type_2_string(tokens[4]));
                }
            }
            else
            {
                printf("MOV EAX, %s\n", token_type_2_string(tokens[0]));
                if (token_type(tokens[4]) == TOKEN_DEFAULT)
                {
                    printf("MUL ");
                    for (int i = 0; i < strlen(tokens[4]); i++)
                    {
                        if (tokens[4][i] == ';')
                        {
                            break;
                        }
                        else
                        {
                            printf("%c", tokens[4][i]);
                        }
                    }
                    printf("\n");
                }
                else
                {
                    printf("MUL %s\n", token_type_2_string(tokens[4]));
                }
                printf("MOV %s, EAX\n", token_type_2_string(tokens[0]));
            }
        }
        else
        {
            // Dacă împărțitorul este 0 atunci se va afisa un mesaj de eroare
            // iar dacă nu se va face logica pentru DIV care e ca la MUL
            if (strcmp(tokens[4], "0;") == 0)
            {
                printf("Error\n");
                return;
            }
            if (token_type(tokens[0]) == EAX)
            {
                if (token_type(tokens[4]) == TOKEN_DEFAULT)
                {
                    printf("DIV ");
                    for (int i = 0; i < strlen(tokens[4]); i++)
                    {
                        if (tokens[4][i] == ';')
                        {
                            break;
                        }
                        else
                        {
                            printf("%c", tokens[4][i]);
                        }
                    }
                    printf("\n");
                }
                else
                {
                    printf("DIV %s\n", token_type_2_string(tokens[4]));
                }
            }
            else
            {
                printf("MOV EAX, %s\n", token_type_2_string(tokens[0]));
                if (token_type(tokens[4]) == TOKEN_DEFAULT)
                {
                    printf("DIV ");
                    for (int i = 0; i < strlen(tokens[4]); i++)
                    {
                        if (tokens[4][i] == ';')
                        {
                            break;
                        }
                        else
                        {
                            printf("%c", tokens[4][i]);
                        }
                    }
                    printf("\n");
                }
                else
                {
                    printf("DIV %s\n", token_type_2_string(tokens[4]));
                }
                printf("MOV %s, EAX\n", token_type_2_string(tokens[0]));
            }
        }
    }
}

// Funcția care se ocupă de conversia din C în ASM
void c_to_asm(char *line, int *token_flag, char *for_register)
{
    char **tokens = NULL;
    int token_count = 0;
    char *token = strtok(line, " \t\n;"); // Împarte linia folosind spațiu, tab sau newline
    while (token != NULL)
    {
        tokens = realloc(tokens, sizeof(char *) * (token_count + 1)); // Realloc pentru a adăuga un nou token
        if (tokens == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        tokens[token_count] = malloc(strlen(token) + 1); // Alocă memorie pentru token
        if (tokens[token_count] == NULL)
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
        printf("%s end_if\n", token_type_2_string(tokens[2]));
        break;
    case TOKEN_WHILE:
        *token_flag = 2;
        printf("start_loop:\n");
        print_func("CMP", tokens[1], tokens[3]);
        printf("%s end_loop\n", token_type_2_string(tokens[2]));
        break;
    case TOKEN_FOR:
        *token_flag = 3;
        strcpy(for_register, tokens[1]); // Salvează registrul pentru a fi folosit mai târziu
        print_func("MOV", tokens[1], tokens[3]);
        printf("start_loop:\n");
        print_func("CMP", tokens[4], tokens[6]);
        printf("%s end_loop\n", token_type_2_string(tokens[5]));
        break;
    case END:
        // Dacă token-ul este END atunci se va verifica ce tip de instrucțiune avem
        // și se va afișa instrucțiunile necesare pentru a termina instrucțiunea
        // iar apoi se va reseta token_flag-ul pentru a putea fi folosit din nou
        if (*token_flag == 1)
        {
            printf("end_label:\n");
            *token_flag = 0;
        }
        else if (*token_flag == 2)
        {
            printf("JMP start_loop\n");
            printf("end_label:\n");
            *token_flag = 0;
        }
        else if (*token_flag == 3)
        {
            print_func("ADD", for_register, "1");
            printf("JMP start_loop\n");
            printf("end_loop:\n");
            *token_flag = 0;
        }
        break;
    default:
        // Verificăm dacă instrucțiunea este o simplă atribuire
        // dacă da atunci se va apela funcția print_func cu MOV ca funcție
        // iar dacă nu se va apela funcția care se ocupă funcțiile de tip simbol
        if (strcmp(tokens[0], tokens[2]) != 0)
        {
            print_func("MOV", tokens[0], tokens[2]);
        }
        else
        {
            symbol_func(tokens);
        }
        break;
    }
    free(tokens);    // Eliberează memoria pentru lista de token-uri
    tokens = NULL;   // Resetează pointerul pentru a evita utilizarea memoriei eliberate
    token_count = 0; // Resetează numărul de token-uri
}