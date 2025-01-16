#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/links.h"
#include "../../include/node.h"

static Link links[MAX_LINKS];
static int link_count = 0;

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

void add_link(const char *name1, const char *name2, char *latency_arg, char *bandwidth_arg)
{

    int latency = DEFAULT_LATENCY;
    int bandwidth = DEFAULT_BANDWIDTH;


    if (latency_arg != NULL) {
        latency = atoi(latency_arg);
    }
    if (bandwidth_arg != NULL) {
        bandwidth = atoi(bandwidth_arg); 
    }

    if (name1 == NULL || name2 == NULL)
    {
        printf("Nom du noeud manquant\n");
        return;
    }
    else
    {
        int i = verify_node(name1);
        int j = verify_node(name2);
        if (i == 999 || j == 999)
        {
            printf("Noeud introuvable\n");
            return;
        }
        if (verify_link(name1, name2) != 999)
        {
            printf("Le lien entre %s et %s existe déjà\n", name1, name2);
            return;
        }
        Link link;
        snprintf(link.node1, 50, "%s", name1);
        snprintf(link.node2, 50, "%s", name2);
        link.latency = latency;
        link.bandwidth = bandwidth;

        links[link_count] = link;
        link_count++;
        printf("Lien ajouté entre %s et %s\n", name1, name2);
    }
}

void list_links() {
    if (link_count == 0) {
        printf("Aucun lien n'a été ajouté.\n");
        return;
    }

    printf("Liste des liens :\n");
    for (int i = 0; i < link_count; i++) {
        printf("  - %s <--> %s (latence : %d ms, bande passante : %d Mbps)\n",
               links[i].node1, links[i].node2, links[i].latency, links[i].bandwidth);
    }
}