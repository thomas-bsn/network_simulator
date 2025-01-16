#include <stdio.h>
#include <string.h>
#include "../include/logger.h"

int main()
{
    char *command = (char *)malloc(MAX_CMD_LEN);
    if (command == NULL) {
        perror("Erreur d'allocation mémoire");
        return 1;
    }

    printf("Bienvenue dans le CLI Network Simulator\n");
    printf("Tapez 'help' pour tester ou 'quit' pour quitter.\n");
    while (1) 
    {
        printf("> "); 
        if (!fgets(command, MAX_CMD_LEN, stdin)) 
            break;

        command[strcspn(command, "\n")] = '\0';
        logger(command);
    }
    free(command);
    return 0;
}


