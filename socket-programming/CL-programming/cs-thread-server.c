/*
CS THREAD ECHO SERVER
201121013 김유석
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>
#include <pthread.h>

#define BACKLOG 10
#define BUFSIZE 1024

struct ThreadArgs {
	int clntSock;
	struct sockaddr_in clntAddr;
};

void *ThreadMain(void *arg);
void child_process(int confd, struct sockaddr_in* clntAddr);

int main(int argc, char* argv[]) {
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	unsigned short servPort;
	unsigned int clntLen;
	int listenfd, connfd;
	pthread_t threadID;
	// create sock
	listenfd = socket(PF_INET, SOCK_STREAM, 0);

	if(argc != 2)
	{
		printf("Usage : %s [port]\n", argv[0]);
		exit(1);
	}

	servPort = atoi(argv[1]);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(servPort);

	bind(listenfd, (struct sockaddr*) &servAddr, sizeof(servAddr));

	listen(listenfd, BACKLOG);

	while(1) {
		clntLen = sizeof(clntAddr);

		connfd = accept(listenfd, (struct sockaddr*) &clntAddr, &clntLen);

		// accept 성공하면 connect를 위한 쓰레드 생성.
		struct ThreadArgs* threadArgs = (struct ThreadArgs*)malloc(sizeof(struct ThreadArgs)); // 쓰레드 생성에 필요한 argument 생성.
		threadArgs->clntSock = connfd; // connect file descriptor
		threadArgs->clntAddr = clntAddr; // client address 정보.

		pthread_create(&threadID, NULL, ThreadMain, (void *)threadArgs);
		printf("%d\n", threadID);
	}
}

void *ThreadMain(void *threadArgs) {
	int clntSock;
	struct sockaddr_in clntAddr;

	pthread_detach(pthread_self());

	clntSock = ((struct ThreadArgs*)threadArgs)->clntSock;
	clntAddr = ((struct ThreadArgs*)threadArgs)->clntAddr;

	free(threadArgs);

	child_process(clntSock, &clntAddr);

	return;
}

void child_process(int confd, struct sockaddr_in* clntAddr) {
	time_t currTime;
	struct tm* currTimeInfo;
	char timeString[26];

	char echoBuffer[BUFSIZE];
	char tempBuffer[BUFSIZE];
	int recvMsgSize;

	int isQuitAndQuit = 0;

	while(1)
	{
		memset(&echoBuffer, 0, sizeof(echoBuffer));
		if((recvMsgSize = recv(confd, echoBuffer, BUFSIZE, 0)) <= 0)
		{
			continue;
		}

		if(!strcmp(echoBuffer, "quit&quit")) {
			// quit&quit 메시지 받으면 종료.
			isQuitAndQuit = 1;
		}

		time(&currTime);
		currTimeInfo = localtime(&currTime);

		// 기존 메시지를 <현재시간> <메시지> <클라이언트 정보> 형태로 가공
		strftime(timeString, 26, "%Y-%m-%d %H:%M:%S", currTimeInfo);
		strcpy(tempBuffer, timeString);
		strcat(tempBuffer, " message : ");
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

		if(send(confd, echoBuffer, recvMsgSize, 0) != recvMsgSize)
		{

		}

		if(isQuitAndQuit == 1) {
			printf("quit&quit. close this socket..\n");
			close(confd);
			exit(1);
		}
	}
}
