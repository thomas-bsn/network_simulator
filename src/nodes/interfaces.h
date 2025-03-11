#ifndef INTERFACES_H
#define INTERFACES_H

#include <stdint.h>

#define MAX_INTERFACES 5 
#define MAX_NETWORK_NAME 20

void generate_mac(char *mac);
void generate_ip(char *ip, int subnet, int node_id);


typedef struct {
    char name[MAX_NETWORK_NAME]; 
    char ip[16];  
    char mac[18]; 
    char gateway[16]; 
} Interface;

#endif // INTERFACES_H
