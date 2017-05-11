#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

char* stu_id = "201121013"; // 학번
int count = 0; // 일련번호

int main(int argc, char* argv[]) {
	int sock, z, msglen;
	struct sockaddr_in mcastAddr;
	char mMsg[1024];
	char temp[1024];
	unsigned char mTTL = 1;
	unsigned int mcastLen;

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// multicast 옵션 추가
	z = setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&mTTL, sizeof mTTL);

	memset(&mcastAddr, 0, sizeof(mcastAddr));
	mcastAddr.sin_family = AF_INET;
	mcastAddr.sin_addr.s_addr = inet_addr("224.10.0.3");
	mcastAddr.sin_port = htons(9010);

	while(1) {
		printf("input message : ");
		fgets(mMsg, 1024, stdin);

		char countString[10];
		sprintf(countString, "%d", count);

		strcpy(temp, stu_id);
		strcat(temp, " ");
		strcat(temp, countString);
		strcat(temp, " ");
		strcat(temp, mMsg);
		strcpy(mMsg, temp);

		msglen = strlen(mMsg);

		if(mMsg[msglen - 1] == '\n') {
			mMsg[msglen-1] = '\0';
		}
		
		z = sendto(sock, mMsg, strlen(mMsg), 0, (struct sockaddr *)&mcastAddr, sizeof mcastAddr);
		count++; // send후에 일련번호 +1
		printf("send message %s\n", mMsg);
		sleep(1);
	}
}
