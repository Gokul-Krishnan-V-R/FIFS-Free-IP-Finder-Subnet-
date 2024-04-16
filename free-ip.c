#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

#define PACKET_SIZE 64
#define TIMEOUT_SEC 1

int ping(const char *host) {
    struct sockaddr_in addr;
    struct timeval timeout;
    struct sockaddr_in *pingaddr = NULL;
    struct icmp *icmp_packet;
    char packet[PACKET_SIZE];
    char recv_packet[PACKET_SIZE];
    int sockfd, bytes_sent, bytes_received;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    struct hostent *host_info;

    host_info = gethostbyname(host);
    if (!host_info) {
        perror("gethostbyname");
        return -1;
    }

    pingaddr = (struct sockaddr_in *) host_info->h_addr_list[0];

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0) {
        perror("socket");
        return -1;
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr = pingaddr->sin_addr;

    icmp_packet = (struct icmp *) packet;
    memset(icmp_packet, 0, PACKET_SIZE);
    icmp_packet->icmp_type = ICMP_ECHO;
    icmp_packet->icmp_code = 0;
    icmp_packet->icmp_id = getpid();
    icmp_packet->icmp_seq = 0;
    gettimeofday((struct timeval *) icmp_packet->icmp_data, NULL);
    icmp_packet->icmp_cksum = 0;
    icmp_packet->icmp_cksum = in_cksum((unsigned short *) icmp_packet, PACKET_SIZE);

    bytes_sent = sendto(sockfd, packet, PACKET_SIZE, 0, (struct sockaddr *) &addr, sizeof(addr));
    if (bytes_sent < 0) {
        perror("sendto");
        return -1;
    }

    timeout.tv_sec = TIMEOUT_SEC;
    timeout.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &timeout, sizeof(timeout)) < 0) {
        perror("setsockopt");
        return -1;
    }

    bytes_received = recvfrom(sockfd, recv_packet, PACKET_SIZE, 0, (struct sockaddr *) &addr, &addr_len);
    if (bytes_received < 0) {
        perror("recvfrom");
        return -1;
    }

    return 0;
}

int main() {
    const char *host = "example.com"; // Change this to your host
    if (ping(host) == 0) {
        printf("Ping to %s successful.\n", host);
    } else {
        printf("Ping to %s failed.\n", host);
    }
    return 0;
}
