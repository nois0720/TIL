#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

#define MAXPENDING 5
#define RCVBUFSIZE 1024
#define ISPAUSE 0 

void pauseUntilInputAnyKey(char* message);
double time_diff(struct timeval x, struct timeval y);

struct protocol {
	unsigned int stu_id;
	unsigned short stu_name_count;
	char* stu_name;
	char* message;
};

int main(int argc, char* argv[]) {
	int sock;
	struct sockaddr_in echoServAddr;
	unsigned short echoServPort;
	char *servIP;
	char echoString[RCVBUFSIZE];
	char echoBuffer[RCVBUFSIZE];
	unsigned int echoStringLen;
	int bytesRcvd;
	int totalBytesRcvd;
	
	if(argc != 4)
	{
		printf("Usage : %s <IP> <Port> <Message>\n", argv[0]);
		exit(1);
	}

	servIP = argv[1];
	echoServPort = atoi(argv[2]);
	strcpy(echoString, argv[3]);
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&echoServAddr, 0, sizeof(echoServAddr));
	echoServAddr.sin_family = AF_INET;
	echoServAddr.sin_addr.s_addr = inet_addr(servIP);
	echoServAddr.sin_port = htons(echoServPort);

	connect(sock, (struct sockaddr*) &echoServAddr, sizeof(echoServAddr));

	int isQuit = 0;
	int count = 0;

	while(1) {
		//printf("input message : ");
		//fgets(echoString, RCVBUFSIZE, stdin);
		echoStringLen = strlen(echoString);

		if(!strcmp(echoString, "quit\n") || !strcmp(echoString, "quit&quit\n")) {
			isQuit = 1;
		}
	
		if(echoString[echoStringLen - 1] == '\n') {
			echoString[echoStringLen-1] = '\0';
		}

		struct timeval now, later;
		gettimeofday(&now, NULL);

		send(sock, echoString, echoStringLen, 0);
		bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0);
		gettimeofday(&later, NULL);
		
		echoBuffer[bytesRcvd] = '\0';
		printf("[RTT : %.01f micro-seconds] echo message : %s\n", time_diff(now,later), echoBuffer);

		if(isQuit == 1) {
			fflush(stdout);
			break;
		}

		count++;
		if(count == 499) break;
	}	

	close(sock);
}

void pauseUntilInputAnyKey(char* message) {
	if(ISPAUSE == 0) return;
	printf("Press any key to continue '%s'...", message);
	getchar();
	puts("");
}

double time_diff(struct timeval x , struct timeval y)
{
	double x_ms , y_ms , diff;

	x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
	y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;

	diff = (double)y_ms - (double)x_ms;

	return diff;
}
