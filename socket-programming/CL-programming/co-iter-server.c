/*
CO ECHO SERVER (modify protocol syntax)
201121013 김유석
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define MAXPENDING 1
#define RCVBUFSIZE 1024

#define ISPAUSE
void HandleTCPClient(int clntSocket, struct sockaddr_in* clntAddr);
void DieWithError(char* errMsg);

int main(int argc, char *argv[]) {
        int servSock;
        int clntSock;
        struct sockaddr_in echoServAddr;
        struct sockaddr_in echoClntAddr;
        unsigned short echoServPort;
        unsigned int clntLen;

        if(argc != 2)
        {
                printf("Usage : %s [port]\n", argv[0]);
                exit(1);
        }

        echoServPort = atoi(argv[1]);

        servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

        memset(&echoServAddr, 0, sizeof(echoServAddr));
        echoServAddr.sin_family = AF_INET;
        echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        echoServAddr.sin_port = htons(echoServPort);

        if(bind(servSock, (struct sockaddr*) &echoServAddr, sizeof(echoServAddr)) == -1)
        {
                DieWithError("bind() error");
        }

        if(listen(servSock, MAXPENDING) == -1)
        {
                DieWithError("listen() error");
        }

        for(;;)
        {
                clntLen = sizeof(echoClntAddr);

                clntSock = accept(servSock, (struct sockaddr*) &echoClntAddr, &clntLen);
                printf("Port : %d , new socket : %d\n", echoServPort, clntSock);
                printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
                HandleTCPClient(clntSock, &echoClntAddr);
        }
        close(servSock);
}

void DieWithError(char* errMsg)
{
        fputs(errMsg, stderr);
        fputc('\n', stderr);
        exit(1);
}

void HandleTCPClient(int clntSocket, struct sockaddr_in* clntAddr) {
    time_t currTime;
    struct tm* currTimeInfo;
    char timeString[26];

    char echoBuffer[RCVBUFSIZE];
    char tempBuffer[RCVBUFSIZE];
    int recvMsgSize;

    int isQuitAndQuit = 0;

    while(1)
    {
        memset(&echoBuffer, 0, sizeof(echoBuffer));
        if((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) <= 0)
        {
            continue;
        }

        if(!strcmp(echoBuffer, "quit&quit")) {
            isQuitAndQuit = 1;
        }

        time(&currTime);
        currTimeInfo = localtime(&currTime);

        strftime(timeString, 26, "%Y-%m-%d %H:%M:%S", currTimeInfo);
        strcpy(tempBuffer, timeString);
        strcat(tempBuffer," message : ");
        strcat(tempBuffer, echoBuffer);
        char port[10];
        sprintf(port, "%d", clntAddr->sin_port);
        strcat(tempBuffer, " port : ");
        strcat(tempBuffer, port);
        strcat(tempBuffer, " address : ");
        strcat(tempBuffer, inet_ntoa(clntAddr->sin_addr));

        strcpy(echoBuffer, tempBuffer);
        recvMsgSize = strlen(echoBuffer);

        printf("%s\n", echoBuffer);
        
        if(send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
        {

        }

        if(isQuitAndQuit == 1) {
            printf("quit&quit. close this socket..\n");
            break;
        }
    }
}
