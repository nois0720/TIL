#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define ECHOMAX 1024

void error_handling(char* message);

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned int cliAddrLen;
    char echoBuffer[ECHOMAX];
    unsigned int echoServPort;
    int recvMsgSize;

    if(argc != 2)
    {
        printf("Usage : %s <Port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if(sock == -1) {
        error_handling("UDP Socket creation error.");
    }

    echoServPort = atoi(argv[1]);
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);

    if(bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) == -1) {
        error_handling("bind() error.");
    }

    int isQuitAndQuit = 0;

    while(1)
    {
        cliAddrLen = sizeof(echoClntAddr);
        recvMsgSize = recvfrom(sock, echoBuffer, sizeof echoBuffer, 0, (struct sockaddr *) &echoClntAddr, &cliAddrLen);

        printf("descriptor : %d. port : %d. client (%s)'s message : %s\n", echoClntAddr.sin_port, echoServPort, inet_ntoa(echoClntAddr.sin_addr), echoBuffer);

		// 받은 메시지가 quit&quit이면 플래그 활성화
        if(!strcmp(echoBuffer, "QUIT&QUIT") | !strcmp(echoBuffer, "quit&quit")) {
            isQuitAndQuit = 1;
        }

		// 메시지 포맷을 (메시지 포트 주소) 형식으로 변경
        strcat(echoBuffer, " port : ");
        char port[10];
        sprintf(port, "%d", echoServPort);
	strcat(echoBuffer, port);
        strcat(echoBuffer, " / addr : ");
        strcat(echoBuffer, inet_ntoa(echoClntAddr.sin_addr));

		// 새롭게 만들어진 메시지 길이로 변경
        recvMsgSize = strlen(echoBuffer);

        sendto(sock, echoBuffer, recvMsgSize, 0, (struct sockaddr *) &echoClntAddr, sizeof(echoClntAddr));

		// 플래그가 활성화되어있으면 소켓 close
        if(isQuitAndQuit == 1) {
            printf("quit&quit. close server socket..\n");
            close(sock);
            exit(1);
        }
    }
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
