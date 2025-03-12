#include <stdio.h>
#include <string.h>
#include "icmp.h"
#include "arp.h"
#include "../../include/node.h"
#include "../network/packet.h"

void sendPing(const char *target_ip, Node *node) 
{
    int index = isInARP(target_ip, node);
    if (index == -1) {
        printf("[ICMP] Adresse MAC inconnue pour %s, envoi d'une requête ARP...\n", target_ip);
        sendARPRequest(target_ip, node);
        return;
    }

    const char *target_mac = node->arp_table[index].mac;
    if (strlen(target_mac) == 0) {
        printf("[ICMP] Erreur : L'entrée ARP pour %s est vide.\n", target_ip);
        return;
    }

    printf("[ICMP] Ping envoyé à %s (%s)...\n", target_ip, target_mac);

    ICMP_Packet icmp_request;
    icmp_request.header.type = TYPE_ICMP;
    icmp_request.type = 8;
    icmp_request.code = 0;
    icmp_request.checksum = 0;

    strncpy(icmp_request.sender_ip, node->ip, sizeof(icmp_request.sender_ip) - 1);
    icmp_request.sender_ip[sizeof(icmp_request.sender_ip) - 1] = '\0';

    strncpy(icmp_request.target_ip, target_ip, sizeof(icmp_request.target_ip) - 1);
    icmp_request.target_ip[sizeof(icmp_request.target_ip) - 1] = '\0';

    receivePacket(&icmp_request, node);
}




void processICMP(ICMP_Packet *packet, Node *node) 
{
    if (packet->type == 8 && strcmp(packet->target_ip, node->ip) == 0) {
        printf("[ICMP] Ping reçu de %s, envoi d'une réponse...\n", packet->sender_ip);

        ICMP_Packet icmp_reply;
        icmp_reply.header.type = TYPE_ICMP;
        icmp_reply.type = 0;
        icmp_reply.code = 0;
        icmp_reply.checksum = 0;

        strncpy(icmp_reply.sender_ip, node->ip, sizeof(icmp_reply.sender_ip) - 1);
        icmp_reply.sender_ip[sizeof(icmp_reply.sender_ip) - 1] = '\0';

        strncpy(icmp_reply.target_ip, packet->sender_ip, sizeof(icmp_reply.target_ip) - 1);
        icmp_reply.target_ip[sizeof(icmp_reply.target_ip) - 1] = '\0';

        receivePacket(&icmp_reply, node);
    }
}