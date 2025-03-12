#ifndef PACKET_H
#define PACKET_H

#define TYPE_ARP  1
#define TYPE_ICMP 2
#define TYPE_TCP  3
#define TYPE_UDP  4

#include "../../include/node.h"

typedef struct {
    int type;  // Type de paquet (ARP, ICMP, TCP, UDP)
} PacketHeader;

typedef struct {
    PacketHeader header;  // Header contenant le type
    char data[512];       // Contenu du paquet
} GenericPacket;

void receivePacket(void *packet, Node *node);

#endif // PACKET_H
