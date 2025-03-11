#ifndef LINKS_H
#define LINKS_H

#define MAX_LINKS 10
#define DEFAULT_LATENCY 1 
#define DEFAULT_BANDWIDTH 100
typedef struct {
    char node1[50];
    char iface1[20];
    char node2[50];
    char iface2[20];
    int latency;
    int bandwidth;
} Link;


extern int link_count;
extern Link links[MAX_LINKS];

int verify_link(const char *name1, const char *name2);
void add_link(const char *node1, const char *iface1, const char *node2, const char *iface2, char *latency_arg, char *bandwidth_arg);
void list_links();

#endif // !LINKS_H