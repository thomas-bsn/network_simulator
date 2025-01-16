#ifndef NODE_H
#define NODE_H

#define MAX_NODES 10

typedef struct {
    int id;
    char name[50];
    char ip[16];
    char mac[18];
} Node;

void add_node(const char *name);
void list_nodes();
void show_node(const char *name);
int verify_node(const char *name);
void remove_node(const char *name);

#endif // !NODE_H