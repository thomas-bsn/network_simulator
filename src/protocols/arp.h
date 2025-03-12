#ifndef ARP_H
#define ARP_H

#include <stdint.h>
#include "../../include/node.h"
#include "../network/packet.h"
#include "arp_table.h"

typedef struct {
    PacketHeader header;
    uint16_t htype;
    uint16_t ptype;
    uint8_t hlen;
    uint8_t plen;
    uint16_t operation;
    char sender_mac[18];
    char sender_ip[16];
    char target_mac[18];
    char target_ip[16];
} ARP_Packet;


int isInARP(const char *ip, Node *node);
void addARPEntry(const char *ip, const char *mac, Node *node);
void sendARPRequest(const char *target_ip, Node *node);
void processARP(ARP_Packet *packet, Node *node);

#endif // ARP_H
