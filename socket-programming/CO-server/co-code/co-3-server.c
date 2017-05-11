#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char* argv[]) {
    int sock, z, msglen;
    struct sockaddr_in mcastAddr, addr;
    char mcastMsg[4096];
    struct ip_mreq mRequest;
    socklen_t addr_len;

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    memset(&mcastAddr, 0, sizeof(mcastAddr));
    mcastAddr.sin_family = AF_INET;
    mcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    mcastAddr.sin_port = htons(9010);

    z = bind(sock, (struct sockaddr *) &mcastAddr, sizeof mcastAddr);

    mRequest.imr_multiaddr.s_addr = inet_addr("224.10.0.15");
    mRequest.imr_interface.s_addr = htonl(INADDR_ANY);

    z = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mRequest, sizeof mRequest);

    while(1)
    {
        addr_len = sizeof(struct sockaddr_in);
        z = recvfrom(sock, mcastMsg, sizeof mcastMsg, 0, (struct sockaddr *) &addr, &addr_len);
        printf("client (%s)'s message : %s\n", inet_ntoa(addr.sin_addr), mcastMsg);
    }
}
