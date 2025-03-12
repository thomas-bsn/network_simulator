#ifndef ARP_TABLE_H
#define ARP_TABLE_H

#define MAX_ARP_ENTRIES 20

typedef struct {
    char ip[16];  
    char mac[18]; 
} ARP_TABLE;

#endif // ARP_TABLE_H
