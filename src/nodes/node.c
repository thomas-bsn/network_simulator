#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/node.h"
#include "../../include/config_parser.h"

Node nodes[MAX_NODES];
int node_count = 0;

void generate_mac(char *mac) 
{
    sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
            (rand() % 256) & ~1, rand() % 256, rand() % 256,
            rand() % 256, rand() % 256, rand() % 256);
}

void generate_ip(char *ip, int node_id) 
{
    int subnet = 1;
    snprintf(ip, 16, "192.168.%d.%d", subnet, node_id);
}



void add_node(const char *name) 
{
    if (name == NULL) 
    {
        printf("Nom du noeud manquant\n");
        return;
    }

    char clean_name[50];
    snprintf(clean_name, sizeof(clean_name), "%s", name);

    for (int i = 0; i < node_count; i++) {
        if (strcmp(nodes[i].name, clean_name) == 0) {
            printf("Le noeud %s existe déjà\n", clean_name);
            return;
        }
    }

    if (node_count < MAX_NODES) {
        Node node;
        node.id = node_count;
        snprintf(node.name, sizeof(node.name), "%s", clean_name);
        generate_ip(node.ip, node.id);
        generate_mac(node.mac);

        nodes[node_count] = node;
        node_count++;
        printf("Noeud ajouté : %s (IP : %s, MAC: %s)\n", node.name, node.ip, node.mac);
        return;
    }
    printf("Nombre maximum de noeuds atteint\n");
}


void list_nodes() 
{
    if (node_count == 0) 
    {
        printf("Aucun nœud n'a été ajouté.\n");
        return;
    }

    printf("Liste des nœuds :\n");
    for (int i = 0; i < node_count; i++) 
        printf("  - %s (IP : %s, MAC : %s)\n",
               nodes[i].name, nodes[i].ip, nodes[i].mac);
}

int verify_node(const char *name)
{
    for (int i = 0; i < node_count; i++)
    {
        if (strcmp(nodes[i].name, name) == 0)
        {
            return i;
        }
    }
    return 999;
}

void show_node(const char *name)
{
    int i = verify_node(name);
    if (i != 999)
    {
        printf("Noeud %s (IP : %s, MAC : %s)\n", nodes[i].name, nodes[i].ip, nodes[i].mac);
    }
    else
    {
        printf("Noeud introuvable : %s\n", name);
    }
}

void remove_node(const char *name)
{
    for (int i = 0; i < node_count; i++)
    {
        if (strcmp(nodes[i].name, name) == 0)
        {
            for (int j = i; j < node_count - 1; j++)
            {
                nodes[j] = nodes[j + 1];
            }
            node_count--;
            printf("Noeud supprimé : %s\n", name);
            return;
        }
    }
    printf("Noeud introuvable : %s\n", name);
}
