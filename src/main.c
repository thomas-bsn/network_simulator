#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/logger.h"
#include "../include/config_parser.h"

int main()
{
    char *command = (char *)malloc(MAX_CMD_LEN);
    if (command == NULL) {
        perror("Erreur d'allocation mémoire");
        return 1;
    }

    const char * config = "src/utils/config.ini";
    if (access(config, F_OK) == 0)
        parse_config(config);

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


