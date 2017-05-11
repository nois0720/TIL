#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

char* stu_id = "201121013"; // 김유석 학번
int count = 0; // 일련번호 count

int main(int argc, char* argv[]) {
	int sock, z, msglen;
	struct sockaddr_in bcastAddr;
	char* bcastIP = "255.255.255.255";
	char bcastMsg[1024];
	char temp[1024];
	int so_broadcast = 1;

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// broadcast 옵션 부여
	z = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *)&so_broadcast, sizeof so_broadcast);

	memset(&bcastAddr, 0, sizeof(bcastAddr));
	bcastAddr.sin_family = AF_INET;
	bcastAddr.sin_addr.s_addr = inet_addr(bcastIP);
	bcastAddr.sin_port = htons(9099);

	while(1) {
		// 메시지 입력
		printf("input message : ");
		fgets(bcastMsg, 1024, stdin);

		// 메시지 포맷을 (학번 일련번호 메시지내용) 으로 변경
		char countString[4];
		sprintf(countString, "%d", count);

		strcpy(temp, stu_id);
		strcat(temp, " ");
		strcat(temp, countString);
		strcat(temp, " ");
		strcat(temp, bcastMsg);
		strcpy(bcastMsg, temp);

		msglen = strlen(bcastMsg);
		
		// '\n'문자열 '\0'로 변경
		if(bcastMsg[msglen - 1] == '\n') {
	             bcastMsg[msglen-1] = '\0';
	    }
		
		sendto(sock, bcastMsg, msglen, 0, (struct sockaddr*) &bcastAddr, sizeof(bcastAddr));
		count++; // send 하고나서 일련번호 +1
		printf("send message %s\n", bcastMsg);
	}
}
