/*
 * pcap-wireshark-김유석.c
 * Network Software LAB-8 pcap_programming
 * 201121013 김유석
*/

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SNAPLEN         68  // size of captured packet (in bytes)
#define MAXPKT          50  // maximum number of stored packets
#define IP_PROTO_TCP	6
#define IP_PROTO_UDP	17

char fileName[1024];	// file name for storing
double init_t;
pcap_t *adhandle;		// selected adaptor for packet capture
pcap_if_t *alldevs;		// pointer for an adpator detected first
pcap_if_t *d;			// pointer for available adaptors
pcap_dumper_t *pd;		// dump file pointer

int cpkNum = 0; // captured packet number
unsigned int pkNum, byteNum;
unsigned int ipNum, tcpNum, udpNum; // ip, tcp, udp packet number

// call back function
void cappkt_save (u_char *user, const struct pcap_pkthdr *h, const u_char *p);

int main(int argc, char *argv[])
{
    char        errbuf[PCAP_ERRBUF_SIZE];
    int         i;              // for general use
    int         ndNum=0;        // number of network devices
    int         devNum;         // device Id used for online packet capture

    /* Retrieve the device list */
    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
        exit(1);
    }

    /* Print the dev list */
    for(d=alldevs; d; d=d->next)
    {
        printf("%d. %s", ++ndNum, d->name);
        if (d->description)
            printf(" (%s)\n", d->description);
        else
            printf(" (No description available)\n");

    }

    /* error ? */
    if(ndNum==0)
    {
        printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
        return -1;
    }

    /* select device for online packet capture application */
    printf("Enter the interface number (1-%d):",ndNum);
    scanf("%d", &devNum);

    /* select error ? */
    if( devNum < 1 || devNum > ndNum)
    {
        printf("\nInterface number out of range.\n");

        /* Free the device list */
        pcap_freealldevs(alldevs);
        return -1;
    }

    /* Jump to the selected adapter */
    for(d=alldevs, i=0; i< devNum-1 ;d=d->next, i++);
    
    /* Open the adapter */
    if ( (adhandle= pcap_open_live(d->name,     // name of the device
                             SNAPLEN,           // captured packet size
                             1,                 // promiscous mode
                             1000,              // read timeout
                             errbuf             // error buffer
                             ) ) == NULL)
    {
        fprintf(stderr,"\nUnable to open the adapter. %s is not supported..\n",d->name);
        /* Free the device list */
        pcap_freealldevs(alldevs);
        return -1;
    }

    printf("\nselected device %s is available\n\n", d->description);

    /* At this point, we don't need any more the device list. Free it */
    pcap_freealldevs(alldevs);

    printf("Enter the file name for storing captured packets : ");
    scanf("%s", fileName);
	strcat(fileName, ".cap");
    
	/* open file for storing captured packets */
    pd = pcap_dump_open( adhandle, fileName);

    /* start the capture */ 
    pkNum=byteNum=ipNum=tcpNum=udpNum=0;
	pcap_loop(adhandle, -1, cappkt_save, (u_char *)pd) ;

    return 0;
}

void cappkt_save (u_char *user, const struct pcap_pkthdr *h, const u_char *p)
{
	int i, ipos = 0;
	struct tm *ltime;
	char timestr[16];
	unsigned short type;
	double crnt_t;

	// convert the timestamp to readable format
	ltime = localtime(&h->ts.tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

	// set init time
	if(cpkNum == 0) 
	{
		init_t = (double)h->ts.tv_sec + 0.000001 * h->ts.tv_usec;
	}
	
	crnt_t = (double) h->ts.tv_sec + 0.000001 * h->ts.tv_usec;
	// display packet header information

	printf("\nNo : %d Time : %.4f ", cpkNum++, crnt_t - init_t);
	// IP datagram
	if ( (type=p[12]<<8 | p[13]) == 0x0800 ) {
		ipNum++;

		printf("(");
		// source IP address
		for(i = 0; i < 4; i++)
			printf("%02d%s",p[i+26], i==3?"->":".");
		
		// destination IP address
		for(i = 0; i < 4; i++)
			printf("%d%s",p[i+30], i==3?")":".");

		if(p[23] == IP_PROTO_UDP)
		{
			udpNum++;
		}
		if(p[23] == IP_PROTO_TCP)
		{
			tcpNum++;
		}

		// upper layer protocol
		printf(" Protocol : %s", p[23]==IP_PROTO_TCP? "TCP":
				p[23]==IP_PROTO_UDP? "UDP":"OTH");
	} else
		printf("(Non-IP)");

	printf(" clen=%d len=%d", h->caplen, h->len);
	
	// store captured packet with WinPcap packet header
	pcap_dump(user, h, p);
	
	// check termination
	if ( cpkNum >= MAXPKT ) {
		printf("\n\n %d-packets were captured.\n", cpkNum);
		printf(" %d-ip datagrams were captured.\n", ipNum);
		printf(" %d-tcp packet were captured.\n", tcpNum);
		printf(" %d-udp packets were captured.\n", udpNum);
		/* close all devices and files */
		pcap_close(adhandle);
		pcap_dump_close(pd);
		exit(0);
	}
}
