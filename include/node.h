#ifndef NODE_H
#define NODE_H

#include "../src/nodes/interfaces.h"
#include "../src/protocols/arp_table.h"

#define MAX_NODES 100
#define MAX_ARP_ENTRIES 20

typedef struct {
    int id;
    char name[50];
    char ip[16];
    char mac[18];
    Interface interfaces[MAX_INTERFACES];
    int interface_count;
    ARP_TABLE arp_table[MAX_ARP_ENTRIES];
} Node;

extern int node_count;
extern Node nodes[MAX_NODES];

void add_node(const char *name);
void list_nodes();
void show_node(const char *name);
int verify_node(const char *name);
void remove_node(const char *name);
void add_interface_to_node(Node *node, const char *network_name, const char *ip, const char *gateway);

#endif // !NODE_H