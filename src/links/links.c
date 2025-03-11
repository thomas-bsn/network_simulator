#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/links.h"
#include "../../include/node.h"

Link links[MAX_LINKS];
int link_count = 0;

int verify_link(const char *name1, const char *name2)
{
    for (int i = 0; i < link_count; i++)
    {
        if (strcmp(links[i].node1, name1) == 0 && strcmp(links[i].node2, name2) == 0)
        {
            return i;
        }
        if (strcmp(links[i].node1, name2) == 0 && strcmp(links[i].node2, name1) == 0)
        {
            return i;
        }
    }
    return 999;
}

void add_link(const char *node1, const char *iface1, const char *node2, const char *iface2, char *latency_arg, char *bandwidth_arg) 
{
    int latency = (latency_arg != NULL) ? atoi(latency_arg) : DEFAULT_LATENCY;
    int bandwidth = (bandwidth_arg != NULL) ? atoi(bandwidth_arg) : DEFAULT_BANDWIDTH;

    if (node1 == NULL || node2 == NULL || iface1 == NULL || iface2 == NULL) {
        printf("Erreur : Nom de nœud ou d'interface manquant\n");
        return;
    }

    int i = verify_node(node1);
    int j = verify_node(node2);
    if (i == 999 || j == 999) {
        printf("Erreur : Un des nœuds n'existe pas\n");
        return;
    }

    int iface1_index = -1, iface2_index = -1;
    for (int k = 0; k < nodes[i].interface_count; k++) {
        if (strcmp(nodes[i].interfaces[k].name, iface1) == 0) {
            iface1_index = k;
            break;
        }
    }
    for (int k = 0; k < nodes[j].interface_count; k++) {
        if (strcmp(nodes[j].interfaces[k].name, iface2) == 0) {
            iface2_index = k;
            break;
        }
    }

    if (iface1_index == -1 || iface2_index == -1) {
        printf("Erreur : Une des interfaces spécifiées n'existe pas\n");
        return;
    }

    for (int k = 0; k < link_count; k++) {
        if ((strcmp(links[k].node1, node1) == 0 && strcmp(links[k].iface1, iface1) == 0 &&
             strcmp(links[k].node2, node2) == 0 && strcmp(links[k].iface2, iface2) == 0) ||
            (strcmp(links[k].node1, node2) == 0 && strcmp(links[k].iface1, iface2) == 0 &&
             strcmp(links[k].node2, node1) == 0 && strcmp(links[k].iface2, iface1) == 0)) {
            printf("Le lien entre %s (%s) et %s (%s) existe déjà\n", node1, iface1, node2, iface2);
            return;
        }
    }

    Link link;
    snprintf(link.node1, 50, "%s", node1);
    snprintf(link.iface1, 20, "%s", iface1);
    snprintf(link.node2, 50, "%s", node2);
    snprintf(link.iface2, 20, "%s", iface2);
    link.latency = latency;
    link.bandwidth = bandwidth;

    links[link_count] = link;
    link_count++;
    printf("Lien ajouté entre %s (%s) et %s (%s) [Latence : %d ms, BP : %d Mbps]\n",
           node1, iface1, node2, iface2, latency, bandwidth);
}


void list_links() 
{
    if (link_count == 0) {
        printf("Aucun lien n'a été ajouté.\n");
        return;
    }

    printf("\nLISTE DES LIENS :\n");
    for (int i = 0; i < link_count; i++) 
    {
        printf("   %s (%s) <--> %s (%s)\n",
               links[i].node1, links[i].iface1, links[i].node2, links[i].iface2);
        printf("      Latence : %d ms | Bande passante : %d Mbps\n",
               links[i].latency, links[i].bandwidth);
    }
}
