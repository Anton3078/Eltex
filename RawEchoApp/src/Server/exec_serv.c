#include "../../include/mysocket.h"

void
handler_serv(struct data_transfer *dts)
{
    struct sembuf wait = {SEM_NOTIFY, -1, 0};
    struct sembuf lock = {SEM_ACCESS, -1, 0};
    struct sembuf unlock = {SEM_ACCESS, 1, 0};

    int sock;
    if ((sock = socket(AF_PACKET, SOCK_RAW, 0)) == -1)
       errExit("socket");

    while (1) {
        semop(semid, &wait, 1);
        semop(semid, &lock, 1);

        if (dts->pk_count > 0) {
            struct packet pkt = dts->pk_hist[0];

            for (int i = 1; i < dts->pk_count; i++) {
                dts->pk_hist[i - 1] = dts->pk_hist[i];
            }
            
            dts->pk_count--;
            
            semop(semid, &unlock, 1);
            
            uint32_t client_ip = pkt.ip.saddr;
            uint32_t client_port = ntohs(pkt.udp.source);
            char *msg = pkt.payload.mtext;
            
            semop(semid, &lock, 1);

            int cli_index = find_client(dts, client_ip, client_port);

            if (cli_index == -1) {
                add_client(dts, client_ip, client_port);
                cli_index = dts->cli_count - 1;
                dts->clients[cli_index].counter = 1; 
            } else {
                dts->clients[cli_index].counter++;
            }
            
            semop(semid, &unlock, 1);

            char response[MAX_MSG + 32];
            snprintf(response, sizeof(response), "%s %u",msg, dts->clients[cli_index].counter);
            strncpy(pkt.payload.mtext, response, MAX_MSG);
            pkt.payload.mtext[MAX_MSG - 1] = '\0';

            swap_mac_address(&pkt);
            swap_ip_address(&pkt);
            swap_udp_ports(&pkt);
            
            pkt.ip.check = 0;
            pkt.ip.check = checksum(&pkt.ip);
            pkt.udp.check = 0;

            pr_pkt_info(&pkt);
            sendto(sock, &pkt, sizeof(pkt), 0, (struct sockaddr *)&pkt.payload.s_addr, sizeof(pkt.payload.s_addr));
        } else {
            semop(semid, &unlock, 1);
        }
    }
}

