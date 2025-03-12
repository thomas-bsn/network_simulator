#include "packet.h"
#include "../protocols/arp.h"
#include "../protocols/icmp.h"
#include "../protocols/tcp.h"
#include "../protocols/udp.h"
#include "../../include/node.h"
#include <stdio.h>

void receivePacket(void *packet, Node *node) 
{
    PacketHeader *header = (PacketHeader *)packet;

    printf("[RECEPTION] Type de paquet reçu : %d\n", header->type);

    switch (header->type) 
    {
        case TYPE_ARP:
            printf("[RECEPTION] Paquet ARP reçu.\n");
            processARP((ARP_Packet *)packet, node);
            break;

        case TYPE_ICMP:
            printf("[RECEPTION] Paquet ICMP reçu.\n");
            processICMP((ICMP_Packet *)packet, node);
            break;

        default:
            printf("[RECEPTION] Type de paquet inconnu (%d).\n", header->type);
    }
}



