/*
 * pcap-analysis-김유석.c
 * Network Software LAB-8 pcap_programming
 * 201121013 김유석
 */
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

/* the include files are valid when it is complied on Linux 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
*/

#define LINE_LEN 16

// litereals realted to distinguishing protocols
#define ETHERTYPE_IP		0x0800
#define ETH_II_HSIZE		14		// frame size of ethernet v2
#define ETH_802_HSIZE		22		// frame size of IEEE 802.3 ethernet
#define IP_PROTO_IP		    0		// IP
#define IP_PROTO_TCP		6		// TCP
#define IP_PROTO_UDP		17		// UDP
#define	RTPHDR_LEN			12		// Length of basic RTP header
#define CSRCID_LEN			4		// CSRC ID length
#define	EXTHDR_LEN			4		// Extension header length

int cpkNum = 1;

unsigned long	net_ip_count;
unsigned long	net_etc_count;
unsigned long	trans_tcp_count;
unsigned long	trans_udp_count;
unsigned long	trans_etc_count;

// Macros
// pntohs : to convert network-aligned 16bit word to host-aligned one
#define pntoh16(p)  ((unsigned short)                       \
                    ((unsigned short)*((unsigned char *)(p)+0)<<8|  \
                     (unsigned short)*((unsigned char *)(p)+1)<<0))

// pntohl : to convert network-aligned 32bit word to host-aligned one
#define pntoh32(p)  ((unsigned short)*((unsigned char *)(p)+0)<<24|  \
                    (unsigned short)*((unsigned char *)(p)+1)<<16|  \
                    (unsigned short)*((unsigned char *)(p)+2)<<8|   \
                    (unsigned short)*((unsigned char *)(p)+3)<<0)

void process_packet(u_char *args,
		const struct pcap_pkthdr *hdr,
		const u_char *packet)
{
	int i;
	unsigned char ip_ver, ip_proto;

	// ip_offset : 14
	ip_ver  = packet[ETH_II_HSIZE]>>4;     // IP version
	ip_proto    = packet[23];        // protocol above IP
	
	unsigned short type;

	// Frame Info
	printf("Frame %d: %5d bytes on wire, %5d bytes captured.\n", cpkNum, hdr->len, hdr->caplen);

	// MAC Address
	printf("ETHERNET 2  src : ");
	for(i = 0; i < 6; i++) printf("%x%s", packet[i+6], i==5 ? " " : ":");
	printf(" dst : ");
	for(i = 0; i < 6; i++) printf("%x%s", packet[i], i==5 ? " " : ":");
	printf("\n");

	// IP datagram
	if((type = pntoh16(&packet[12])) == 0x0800) {
		net_ip_count++;
		
		printf("Internet Protocol Version %d:  src : ", ip_ver);
		for(i = 0; i < 4; i++)
			printf("%d%s", packet[i+26], i==3?" ":".");
		printf(" dst : ");
		for(i = 0; i < 4; i++)
			printf("%d%s", packet[i+30], i==3?" ":".");
		printf("\n");
		
		if(ip_proto == IP_PROTO_UDP) {
			trans_udp_count++;

			// UDP
			printf("User Datagram Protocol: ");
			printf("Src port : %d  ", packet[i+30] * 16 * 16 + packet[i+31]);
			printf("Dst port : %d\n", packet[i+32] * 16 * 16 + packet[i+33]);
			printf("\n");
//			printf("Src port : %x%x\n", packet[i+30], packet[i+31]);
		}
		if(ip_proto == IP_PROTO_TCP) { 
			trans_tcp_count++;

			// TCP
			printf("Transmission Control Protocol: ");
			printf("Src port : %d  ", packet[i+30] * 16 * 16 + packet[i+31]);
			printf("Dst port : %d\n", packet[i+32] * 16 * 16 + packet[i+33]);
			printf("\n");
//			printf("Src port : %x%x\n", packet[i+30], packet[i+31]);
		}
		
	} else {
		net_etc_count++;
	}

	cpkNum++;
}

int main(int argc, char **argv)
{
	pcap_t *pcap;
	const unsigned char *packet;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct pcap_pkthdr header;

	if(argc != 2) {
		printf("usage : %s <filename>\n", argv[0]);
		exit(1);
	}

	pcap = pcap_open_offline(argv[1], errbuf);

	if(pcap == NULL) {
		fprintf(stderr, "error reading pcap file: %s\n", errbuf);
		exit(1);
	}

	pcap_loop(pcap, -1, process_packet, 0);
	printf("%d-ip packets captured\n", net_ip_count);
	printf("%d-udp packets captured\n", trans_udp_count);
	printf("%d-tcp packets captured\n", trans_tcp_count);
	return 0;
}
