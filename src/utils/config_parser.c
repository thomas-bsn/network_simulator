#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/config_parser.h"
#include "../../include/node.h"
#include "../../include/links.h"

void trim(char *str) 
{
    if (str == NULL || *str == '\0') return;
    char *start = str;
    while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r') {
        start++;
    }
    char *end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        *end = '\0';
        end--;
    }
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}


void parse_config(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int mode = 0; // 1 = Nodes, 2 = Links

    while (fgets(line, sizeof(line), file)) {
        trim(line);
        if (line[0] == '[') {
            if (strstr(line, "[Nodes]")) mode = 1;
            else if (strstr(line, "[Links]")) mode = 2;
            continue;
        }

        if (mode == 1 && strchr(line, '=')) {
            strtok(line, "="); // Ignore la clé
            char *value = strtok(NULL, "=");
            trim(value);
            add_node(value);
        } 
        else if (mode == 2 && strchr(line, '=')) {
            strtok(line, "="); // Ignore la clé
            char *value = strtok(NULL, "=");
            trim(value);

            // Extraction des valeurs
            char node1[50], node2[50], latency[10] = "", bandwidth[10] = "";
            int parsed = sscanf(value, "%49[^,],%49[^,],%9[^,],%9s", node1, node2, latency, bandwidth);

            if (parsed >= 2) {
                char *latency_arg = (parsed >= 3 && latency[0] != '\0') ? latency : NULL;
                char *bandwidth_arg = (parsed == 4 && bandwidth[0] != '\0') ? bandwidth : NULL;
                add_link(node1, node2, latency_arg, bandwidth_arg);
            } else {
                printf("Format de lien incorrect dans config.ini: %s\n", line);
            }
        }
    }

    fclose(file);
    printf("==== Configuration chargée ====\n");
    printf("\n");
}

void print_config() 
{
    printf("Nodes:\n");
    for (int i = 0; i < node_count; i++)
        printf("- %s\n", nodes[i].name);

    printf("\nLinks:\n");
    for (int i = 0; i < link_count; i++)
        printf("- %s <-> %s\n", links[i].node1, links[i].node2);
}