#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaces.h"


void generate_mac(char *mac) 
{
    sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X",
            (rand() % 256) & ~1, rand() % 256, rand() % 256,
            rand() % 256, rand() % 256, rand() % 256);
}

void generate_ip(char *ip, int subnet, int node_id) {
    snprintf(ip, 16, "192.168.%d.%d", subnet, node_id);
}
