#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/logger.h"
#include "../../include/node.h"
#include "../../include/links.h"
#include "../../include/config_parser.h"

void logger(char *command) 
{
    char *cmd_copy = strdup(command);
    if (cmd_copy == NULL) {
        perror("Erreur d'allocation mémoire");
        return;
    }

    // Découpe la commande en tokens
    char *token = strtok(cmd_copy, " ");
    if (token == NULL) {
        printf("Commande vide.\n");
        free(cmd_copy);
        return;
    }


    if (strcmp(token, "help") == 0) 
    {
        printf("Liste des commandes disponibles :\n");
        printf("- help : Affiche la liste des commandes disponibles\n");
        printf("- add_node [NOM] : Ajoute un noeud\n");
        printf("- list_nodes : Liste les noeuds\n");
        printf("- show_node [NOM] : Affiche les informations d'un noeud\n");
        printf("- remove_node [NOM] : Supprime un noeud\n");
        printf("- add_link [NOM1] [INTERFACE1] [NOM2] [INTERFACE2] [LATENCE] [BANDE PASSANTE] : Ajoute un lien entre deux noeuds\n");
        printf("- list_links : Liste les liens\n");
        printf("- add_interface [NOM] [RESEAU] [IP] [PASSERELLE] : Ajoute une interface à un noeud\n");
        printf("- config : Affiche la configuration\n");
        printf("- clear : Efface l'écran\n");
        printf("- quit : Quitte le programme\n");
    } 
    else if (strcmp(token, "add_node") == 0) 
    {
        char *node_name = strtok(NULL, " ");
        add_node(node_name);
    } 
    else if (strcmp(token, "list_nodes") == 0) 
    {
        list_nodes();
    } 
    else if (strcmp(token, "add_link") == 0) 
    {
        char *node1 = strtok(NULL, " ");
        char *iface1 = strtok(NULL, " ");
        char *node2 = strtok(NULL, " ");
        char *iface2 = strtok(NULL, " ");
        char *latency = strtok(NULL, " ");
        char *bandwidth = strtok(NULL, " ");

        if (node1 == NULL || iface1 == NULL || node2 == NULL || iface2 == NULL) {
            printf("Erreur : Syntaxe incorrecte.\n");
            printf("Utilisation : add_link <node1> <interface1> <node2> <interface2> [latency] [bandwidth]\n");
            return;
        }

        add_link(node1, iface1, node2, iface2, latency, bandwidth);
    }
    else if (strcmp(token, "list_links") == 0) 
    {
        list_links();
    }
    else if (strcmp(token, "show_node") == 0) 
    {
        char *node_name = strtok(NULL, " ");
        if (node_name == NULL) {
            printf("Erreur : Aucun nom de noeud fourni.\n");
        } else {
            show_node(node_name);
        }
    }
    else if (strcmp(token, "remove_node") == 0) 
    {
        char *node_name = strtok(NULL, " ");
        remove_node(node_name);
    }
    else if (strcmp(command, "clear") == 0) 
    {
        printf("\033[H\033[J");
    } 
    else if (strcmp(token, "add_interface") == 0) 
    {
        char *node_name = strtok(NULL, " ");
        char *iface_name = strtok(NULL, " ");
        char *ip = strtok(NULL, " ");
        char *gateway = strtok(NULL, " ");

        if (node_name == NULL || iface_name == NULL || ip == NULL || gateway == NULL) {
            printf("Erreur : Syntaxe incorrecte.\n");
            printf("Utilisation : add_interface <node> <interface_name> <IP> <Gateway>\n");
            return;
        }

        int node_index = verify_node(node_name);
        if (node_index == 999) {
            printf("Erreur : Noeud %s introuvable.\n", node_name);
            return;
        }

        add_interface_to_node(&nodes[node_index], iface_name, ip, gateway);
    }

    else if (strcmp(command, "config") == 0) 
    {
        print_config();
    }
    else if ((strcmp(command, "quit") == 0) || (strcmp(command, "exit") == 0) || (strcmp(command, "q") == 0))
    {
        free(cmd_copy);
        exit(0);
    } 
    else 
    {
        printf("Commande inconnue : %s\n", command);
    }
    free(cmd_copy);
}
