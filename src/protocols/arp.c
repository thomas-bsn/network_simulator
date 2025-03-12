#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arp.h"
#include "../../include/node.h"
#include "../network/packet.h"


int isInARP(const char *ip, Node *node) // Vérifier si une entrée ARP existe
{
    for (int i = 0; i < MAX_ARP_ENTRIES; i++)
    {
        if (strlen(node->arp_table[i].ip) > 0 && strcmp(node->arp_table[i].ip, ip) == 0)
        {
            return i;
        }
    }
    return -1;
}


void addARPEntry(const char *ip, const char *mac, Node *node) // Ajouter une entrée ARP
{
    int i = isInARP(ip, node);
    if (i != -1)
    {
        printf("L'entrée ARP pour %s existe déjà.\n", ip);
        return;
    }

    for (int i = 0; i < MAX_ARP_ENTRIES; i++)
    {
        if (strlen(node->arp_table[i].ip) == 0)
        {
            strncpy(node->arp_table[i].ip, ip, 16);
            strncpy(node->arp_table[i].mac, mac, 18);
            printf("Nouvelle entrée ARP ajoutée : %s -> %s\n", ip, mac);
            return;
        }
    }
    printf("Table ARP pleine.\n");
}

void sendARPRequest(const char *target_ip, Node *node) // Envoyer une requête ARP
{
    ARP_Packet request;
    request.operation = 1; // ARP Request
    strncpy(request.sender_mac, node->mac, 18);
    strncpy(request.sender_ip, node->ip, 16);
    strncpy(request.target_mac, "00:00:00:00:00:00", 18); // Inconnu
    strncpy(request.target_ip, target_ip, 16);

    printf("ARP Request envoyé : Qui a l'IP %s ?\n", target_ip);
}


void processARP(ARP_Packet *packet, Node *node) 
{
    if (packet->operation == 1) { // Requête ARP reçue
        printf("[ARP] Requête reçue : Qui a l'IP %s ?\n", packet->target_ip);

        if (strcmp(packet->target_ip, node->ip) == 0) {
            printf("[ARP] Je suis la cible ! Envoi de la réponse ARP...\n");

            ARP_Packet reply;
            reply.header.type = TYPE_ARP;  // ✅ Définir le type ARP
            reply.htype = packet->htype;
            reply.ptype = packet->ptype;
            reply.hlen = packet->hlen;
            reply.plen = packet->plen;
            reply.operation = 2; // Réponse ARP

            strncpy(reply.sender_mac, node->mac, sizeof(reply.sender_mac) - 1);
            reply.sender_mac[sizeof(reply.sender_mac) - 1] = '\0';

            strncpy(reply.sender_ip, node->ip, sizeof(reply.sender_ip) - 1);
            reply.sender_ip[sizeof(reply.sender_ip) - 1] = '\0';

            strncpy(reply.target_mac, packet->sender_mac, sizeof(reply.target_mac) - 1);
            reply.target_mac[sizeof(reply.target_mac) - 1] = '\0';

            strncpy(reply.target_ip, packet->sender_ip, sizeof(reply.target_ip) - 1);
            reply.target_ip[sizeof(reply.target_ip) - 1] = '\0';

            receivePacket(&reply, node);
        }
    } 
    else if (packet->operation == 2) { // Réponse ARP reçue
        printf("[ARP] Réponse reçue : %s -> %s\n", packet->sender_ip, packet->sender_mac);
        addARPEntry(packet->sender_ip, packet->sender_mac, node);
    }
}
