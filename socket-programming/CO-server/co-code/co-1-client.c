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
	struct sockaddr_in fromAddr;
	unsigned short echoServPort;
	unsigned int fromSize;
	char *servIp;
	char echoString[ECHOMAX];
	char echoBuffer[ECHOMAX];
	int echoStringLen;
	int respStringLen;
	int sendStringLen;

	if(argc != 3)
	{
		printf("Usage : %s <Server IP> <Port>\n", argv[0]);
		exit(1);
	}

	servIp = argv[1];
	echoServPort = atoi(argv[2]);

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(sock == -1) {
		error_handling("socket() error");
	}

	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIp);
	echoServAddr.sin_port = htons(echoServPort);

	while(1)
	{
		printf("Insert message(q to quit) : ");
		fgets(echoString, ECHOMAX, stdin);

		echoStringLen = strlen(echoString);

		if(echoString[echoStringLen - 1] == '\n') {
			echoString[echoStringLen-1] = '\0';
		}

		// send 및 보낸 스트링의 길이 출력
		sendStringLen = sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr));
		printf("send string's length : %d\n", sendStringLen);

		// recv 및 받은 스트링 길이 저장 
		fromSize = sizeof(fromAddr);
		respStringLen = recvfrom(sock, echoBuffer, ECHOMAX, 0, (struct sockaddr *) &fromAddr, &fromSize);

		printf("[S -> C] echo message : %s\n", echoBuffer);

		// q 혹은 quit&quit 메시지면 소켓 close
		if(!strcmp(echoString, "q") || !strcmp(echoString, "Q") || !strcmp(echoString, "quit&quit") || !strcmp(echoString, "QUIT&QUIT")) {
			printf("close socket..\n");
			break;
		}

		printf("recv string's length : %d\n", respStringLen);
	}
	close(sock);
}

void error_handling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
