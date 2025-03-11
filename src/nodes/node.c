#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaces.h"
#include "../../include/node.h"
#include "../../include/config_parser.h"

Node nodes[MAX_NODES];
int node_count = 0;



void add_interface_to_node(Node *node, const char *network_name, const char *ip, const char *gateway) 
{
    if (node->interface_count >= MAX_INTERFACES) {
        printf("Erreur : Le noeud %s a atteint le nombre maximum d'interfaces.\n", node->name);
        return;
    }

    Interface *iface = &node->interfaces[node->interface_count];
    strncpy(iface->name, network_name, MAX_NETWORK_NAME);
    strncpy(iface->ip, ip, 16);
    strncpy(iface->gateway, gateway, 16);
    generate_mac(iface->mac);

    printf("Interface ajoutée à %s -> Réseau : %s, IP : %s, MAC : %s, Passerelle : %s\n",
           node->name, iface->name, iface->ip, iface->mac, iface->gateway);

    node->interface_count++;
}

void add_node(const char *name) 
{
    if (name == NULL) {
        printf("Nom du noeud manquant\n");
        return;
    }

    if (node_count >= MAX_NODES) {
        printf("Nombre maximum de noeuds atteint\n");
        return;
    }

    Node *node = &nodes[node_count];
    node->id = node_count;
    strncpy(node->name, name, 50);
    node->interface_count = 0;

    char ip[16];
    generate_ip(ip, 1, node->id);
    add_interface_to_node(node, "LAN", ip, "192.168.1.1");

    node_count++;
    printf("Noeud ajouté : %s avec une interface réseau %s (IP : %s)\n",
           node->name, node->interfaces[0].name, node->interfaces[0].ip);
}

void list_nodes() 
{
    if (node_count == 0) 
    {
        printf("Aucun nœud n'a été ajouté.\n");
        return;
    }

    printf("\nLISTE DES NOEUDS :\n");
    for (int i = 0; i < node_count; i++) 
    {
        if (nodes[i].interface_count > 0) {
            Interface *iface = &nodes[i].interfaces[0]; // Prend la première interface
            printf("  - %s (IP : %s, MAC : %s)\n",
                   nodes[i].name, iface->ip, iface->mac);
        } else {
            printf("  - %s (Aucune interface configurée)\n", nodes[i].name);
        }
    }
    printf("\n");
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
    if (i == 999) {
        printf("Noeud introuvable : %s\n", name);
        return;
    }

    Node *node = &nodes[i];

    printf("\n==== INFOS DU NOEUD ====\n");
    printf("Nom       : %s\n", node->name);
    printf("ID        : %d\n", node->id);
    printf("Interfaces : %d\n", node->interface_count);

    if (node->interface_count == 0) {
        printf("   ⚠ Aucun réseau configuré.\n");
    } else {
        for (int j = 0; j < node->interface_count; j++) {
            Interface *iface = &node->interfaces[j];
            printf("    Interface %d\n", j + 1);
            printf("      - Réseau : %s\n", iface->name);
            printf("      - IP      : %s\n", iface->ip);
            printf("      - MAC     : %s\n", iface->mac);
            printf("      - Gateway : %s\n", iface->gateway);
        }
    }

    printf("=========================\n\n");
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
