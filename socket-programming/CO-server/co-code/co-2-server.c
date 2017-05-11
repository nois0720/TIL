#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char* argv[]) {
    int sock, z, msglen;
    struct sockaddr_in bcastAddr;
    struct sockaddr_in addr;
    socklen_t addr_len;
    char* bcastIP = "255.255.255.255";
    char recvMsg[4096];

    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    memset(&bcastAddr, 0, sizeof(bcastAddr));
    bcastAddr.sin_family = AF_INET;
    bcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bcastAddr.sin_port = htons(8099);

    z = bind(sock, (struct sockaddr *) &bcastAddr, sizeof bcastAddr);

    while(1)
    {
        addr_len = sizeof(struct sockaddr_in);
        z = recvfrom(sock, recvMsg, sizeof recvMsg, 0, (struct sockaddr *) &addr, &addr_len);
        printf("client (%s)'s message : %s\n", inet_ntoa(addr.sin_addr), recvMsg);
    }
}
