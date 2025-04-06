#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

int main()
{
    // Alocă memorie pentru token_flag și inițializează cu 0 apoi verific dacă alocarea a avut succes
    int *token_flag = calloc(1, sizeof(int));
    if (!token_flag)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }
    // Alocă memorie pentru for_register și verific dacă alocarea a avut succes
    char *for_register = malloc(4 * sizeof(char));
    if (!for_register)
    {
        fprintf(stderr, "Memory allocation failed\n");
        // Eliberează memoria alocată pentru token_flag
        free(token_flag);
        return -1;
    }

    char line[MAX_LINE_LENGTH]; // Dimensiunea maximă a liniei

    while (1)
    {
        if (!fgets(line, sizeof(line), stdin))
        {
            break; // Eroare la citirea liniei
        }

        if (strcmp(line, "\n") == 0)
        {
            break; // Ieșire din buclă
        }

        c_to_asm(line, token_flag, for_register); // Apelează funcția c_to_asm pentru a procesa linia
    }

    free(for_register);  // Eliberează memoria alocată pentru for_register
    for_register = NULL; // Resetează pointerul pentru a evita utilizarea memoriei eliberate
    free(token_flag);    // Eliberează memoria alocată pentru token_flag
    token_flag = NULL;   // Resetează pointerul pentru a evita utilizarea memoriei eliberate
    return 0;
}