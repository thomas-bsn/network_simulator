#include "event_loop.h"
#include "../../include/node.h"
#include "../protocols/arp.h"
#include "../protocols/icmp.h"
#include "../network/packet.h"
#include <stdio.h>
#include <unistd.h>  
#include <string.h> 

void runEventLoop() 
{
    Node nodes[2] = {
        {.id = 1, .ip = "192.168.1.10", .mac = "AA:BB:CC:DD:EE:10"},
        {.id = 2, .ip = "192.168.1.20", .mac = "AA:BB:CC:DD:EE:20"}
    };

    int running = 1;
    int iteration = 0;

    while (running) {
        printf("\n--- [ EVENT LOOP : ITÉRATION %d ] ---\n", iteration++);

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (i == j) continue;

                printf("\n[TEST] Node%d (%s) essaie de contacter Node%d (%s)...\n", 
                       nodes[i].id, nodes[i].ip, nodes[j].id, nodes[j].ip);

                int index = isInARP(nodes[j].ip, &nodes[i]);
                if (index == -1) {
                    printf("[ARP] Node%d ne connaît pas Node%d. Envoi d'une requête ARP...\n",
                           nodes[i].id, nodes[j].id);
                    sendARPRequest(nodes[j].ip, &nodes[i]);
                
                    // Simulation de la requête ARP
                    ARP_Packet arp_request;
                    arp_request.header.type = TYPE_ARP;
                    arp_request.htype = 1;
                    arp_request.ptype = 0x0800;
                    arp_request.hlen = 6;
                    arp_request.plen = 4;
                    arp_request.operation = 1;

                    strncpy(arp_request.sender_mac, nodes[i].mac, sizeof(arp_request.sender_mac) - 1);
                    arp_request.sender_mac[sizeof(arp_request.sender_mac) - 1] = '\0';

                    strncpy(arp_request.sender_ip, nodes[i].ip, sizeof(arp_request.sender_ip) - 1);
                    arp_request.sender_ip[sizeof(arp_request.sender_ip) - 1] = '\0';

                    strncpy(arp_request.target_mac, "00:00:00:00:00:00", sizeof(arp_request.target_mac) - 1);
                    arp_request.target_mac[sizeof(arp_request.target_mac) - 1] = '\0';

                    strncpy(arp_request.target_ip, nodes[j].ip, sizeof(arp_request.target_ip) - 1);
                    arp_request.target_ip[sizeof(arp_request.target_ip) - 1] = '\0';

                    receivePacket(&arp_request, &nodes[j]);
                }

                printf("\n[ICMP] Node%d envoie un ping à Node%d...\n", nodes[i].id, nodes[j].id);
                sendPing(nodes[j].ip, &nodes[i]);

                sleep(1);
            }
        }

        if (iteration >= 2) running = 0;
    }

    printf("\n--- [ FIN DE LA SIMULATION ] ---\n");
}
