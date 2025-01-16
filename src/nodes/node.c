#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/node.h"

static Node nodes[MAX_NODES];
static int node_count = 0;

char *generate_mac()
{
    char *mac = (char *)malloc(18);
    if (mac == NULL)
    {
        perror("Erreur d'allocation mémoire");
        return NULL;
    }

    sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
        (rand() % 256) & ~1, rand() % 256, rand() % 256,
        rand() % 256, rand() % 256, rand() % 256);

    return mac;
}

char *generate_ip(int node_id) 
{
    int subnet = 1;
    char *ip = (char *)malloc(16);
    if (ip == NULL) {
        perror("Erreur d'allocation mémoire");
        return NULL;
    }

    snprintf(ip, 16, "192.168.%d.%d", subnet, node_id);
    return ip;
}


void add_node(const char *name)
{
    if (name == NULL)
    {
        printf("Nom du noeud manquant\n");
        return;
    }
    else
    {
        for(int i = 0; i < node_count; i++)
        {
            if (strcmp(nodes[i].name, name) == 0)
            {
                printf("Le noeud %s existe déjà\n", name);
                return;
            }
        }
    }
    if (node_count < MAX_NODES)
    {
        Node node;
        node.id = node_count;
        snprintf(node.name, 50, "%s", name);
        snprintf(node.ip, 16, "%s", generate_ip(node.id));
        snprintf(node.mac, 18, "%s", generate_mac());

        nodes[node_count] = node;
        node_count++;
        printf("Noeud ajouté : %s (IP : %s, Nom: %s, MAC: %s)\n", name, node.ip, node.name, node.mac);
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