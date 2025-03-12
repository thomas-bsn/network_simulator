#ifndef ICMP_H
#define ICMP_H

#include <stdint.h>

#include "../../include/node.h"
#include "../network/packet.h"

typedef struct {
    PacketHeader header;  
    uint8_t type;      // 8 = Echo Request, 0 = Echo Reply
    uint8_t code;      // Toujours 0 pour ping
    uint16_t checksum;
    char sender_ip[16];
    char target_ip[16];
} ICMP_Packet;


void processICMP(ICMP_Packet *packet, Node *node);
void sendPing(const char *target_ip, Node *node);

#endif // ICMP_H
