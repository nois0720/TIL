/*
CS FORK ECHO SERVER.
201121013 김유석
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <time.h>

#define BACKLOG 10
#define BUFSIZE 1024

void child_process(int confd, struct sockaddr_in* clntAddr);

int main(int argc, char* argv[]) {
	struct sockaddr_in servAddr;
	struct sockaddr_in clntAddr;
	unsigned short servPort;
	unsigned int clntLen;
	pid_t pid;
	int listenfd, connfd;

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

	// bind socket with ip, port
	bind(listenfd, (struct sockaddr*) &servAddr, sizeof(servAddr));
	listen(listenfd, BACKLOG);

	while(1) {
		clntLen = sizeof(clntAddr);

		connfd = accept(listenfd, (struct sockaddr*) &clntAddr, &clntLen);
		
		// Accept에 성공하면, fork를 통해 새로운 프로세스를 생성
		pid = fork();
		printf("pid : %d\n", pid);

		if(pid == 0) { // child
			// child는 listen 소켓을 닫음.
			close(listenfd);
			child_process(connfd, &clntAddr);
		}

		// 부모는 connect를 위한 소켓을 닫음.
		close(connfd);
	}

	close(connfd);
}

void child_process(int confd, struct sockaddr_in* clntAddr) {
	time_t currTime; // 현재 시간을 저장하기 위한 time_t 변수
	struct tm* currTimeInfo;
	char timeString[26]; // time stamp

	char echoBuffer[BUFSIZE]; // 에코를 위한 버퍼 
	char tempBuffer[BUFSIZE]; // 돌려줄 메시지 가공을 위한 버퍼
	int recvMsgSize; // 받은 메시지 크기

	int isQuitAndQuit = 0; // 1이면 아래 루프 빠져나옴.

	while(1)
	{
		memset(&echoBuffer, 0, sizeof(echoBuffer));
		if((recvMsgSize = recv(confd, echoBuffer, BUFSIZE, 0)) <= 0)
		{
			continue;
		}


		if(!strcmp(echoBuffer, "quit&quit")) {
			// quit&quit이면 종료
			isQuitAndQuit = 1;
		}

		time(&currTime);
		currTimeInfo = localtime(&currTime);

		// 메시지 포맷을 <현재시간> <메시지> <클라이언트 정보> 로 수정
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
