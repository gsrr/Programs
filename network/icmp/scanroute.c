/**********************************************************************
 *  掃描路徑範例程式 (scanroute.c)
 *        Ver 1.0 2001年7月10日
 *                                製作‧著作　村山公保(Yukio Murayama)
 *
 *  使用承諾書
 *    本程式只供學習TCP/IP協定以及提升網路程式設計的技能，
 *    可以原封不動地或加以修正地使用。禁止使用或改造本程式
 *    於違反法律或善良風俗的事物。本程式不做任何保證。因由
 *    本程式所產生的損害，著者不負擔任何責任。
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#define __FAVOR_BSD
#include <netinet/udp.h>
#include <arpa/inet.h>

enum {CMD_NAME, DST_IP};
enum {ON, OFF};

#define MAXHOSTNAMELEN 256
#define BUFSIZE        512

struct packet_udp {
	struct ip ip;
	struct udphdr udp;
};

void make_ip_header(struct ip *ip, int srcip, int dstip, int iplen);
void make_udp_header(struct udphdr *udp);
void tvsub(struct timeval *out, struct timeval *in);
u_short checksum(u_short *data, int len);

int main(int argc, char *argv[])
{ 
	struct packet_udp sendpacket; /* 發送UDP/IP封包         */
	struct sockaddr_in send_sa;   /* 終點址                  */
	int send_sd;                  /* 發送用接口描述碼        */
	int recv_sd;                  /* 接收用接口描述碼        */
	int len;                      /* 發送用IP封包長度       */
	int ttl;                      /* TTL值                   */
	int i;                        /* 迴環變數                 */
	u_char buff[BUFSIZE];         /* 接收緩衝器               */
	struct timeval tvm0;          /* 發送封包時刻              */
	struct timeval tvm1;          /* 接收封包時刻              */
	struct timeval tv;            /* select的暫停計時         */
	fd_set readfd;                /*  用select檢查描述碼 */
	int on = 1;                   /* ON                        */
	int dns_flg = ON;             /* 是否檢索主機的域名        */

	/* 檢查自變數-n選項 */
	if (argc == 3 && strcmp(argv[1],"-n") == 0) {
		dns_flg = OFF;
		argv[1] = argv[2];
		argv[2] = NULL;
		argc = 2;
	}

	/* 檢查自變數 */
	if (argc != 2) {
		fprintf(stderr, "usage: %s [-n] dst_ip\n", argv[CMD_NAME]);
		exit(EXIT_FAILURE);
	}

	memset((char *) &send_sa, 0, sizeof(struct sockaddr_in));
	send_sa.sin_family = AF_INET;

	/* 從域名轉換成IP址 */
	if ((send_sa.sin_addr.s_addr = inet_addr(argv[DST_IP])) == INADDR_NONE) {
		struct hostent *he;  /* 主機資訊 */

		if ((he = gethostbyname(argv[DST_IP])) == NULL) {
			fprintf(stderr, "unknown host %s\n", argv[DST_IP]);
			exit(EXIT_FAILURE);
		}
		send_sa.sin_family = he->h_addrtype;
		memcpy((char *) &(send_sa.sin_addr), he->h_addr, sizeof(he->h_length));
	}

	/* 打開UDP/IP發送用RAW接口 */
	if ((send_sd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
		perror("socket(SOCK_RAW)");
		exit(EXIT_FAILURE);
	}

	if (setsockopt(send_sd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0) {
		perror("setsockopt(IPPROTO_IP, IP_HDRINCL)");
		exit(EXIT_FAILURE);
	}

	/* 打開ICMP接收用RAW接口 */
	if ((recv_sd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
		perror("socket(SOCK_RAW)");
		exit(EXIT_FAILURE);
	}

	/* 製作UDP/IP封包 */
	len = sizeof(struct packet_udp);
	memset((char *)&sendpacket, 0, sizeof(struct packet_udp));
	make_udp_header(&(sendpacket.udp));
	make_ip_header(&(sendpacket.ip), 0, send_sa.sin_addr.s_addr, len);

	/*
	 *  掃描路徑主常式
	 */
	printf("scanroute %s\n", inet_ntoa(send_sa.sin_addr));
	for (ttl = 1; ttl <= 64; ttl++) {
		printf("%2d: ", ttl);
		fflush(stdout);

		sendpacket.ip.ip_ttl = ttl;

		for (i = 0; i < 3; i++) {
			/* 發送UDP封包 */
			if (sendto(send_sd, (char *)&sendpacket, len, 0, 
						(struct sockaddr *) &send_sa, sizeof send_sa) < 0) {
				perror("sendto");
				exit(EXIT_FAILURE);
			}

			/* 記錄發送時刻 */
			gettimeofday(&tvm0, (struct timezone *)0);

			/* 設定select的暫停計時 */
			tv.tv_sec  = 3;
			tv.tv_usec = 0;
reread:
			/* 利用select檢查描述碼的設定 */
			FD_ZERO(&readfd);
			FD_SET(recv_sd, &readfd);

			if ((select(recv_sd + 1, &readfd, NULL, NULL, &tv)) > 0) {
				int hlen;              /* 起始碼長度            */
				struct icmp *icmp;     /* ICMP結構體            */
				struct ip *ip;         /* IP結構體              */
				struct hostent *host;  /* 主機資訊              */
				char hostip[256];      /* 表示IP址的字串     */
				struct in_addr ipaddr; /* IP址結構體            */

				/* 接收ICMP封包 */
				if (recvfrom(recv_sd, buff, BUFSIZE, 0, NULL, NULL) < 0) {
					perror("recvfrom");
					exit(EXIT_FAILURE);
				}

				ip = (struct ip *)buff;
				hlen = ip->ip_hl << 2;

				if (ip->ip_p != IPPROTO_ICMP)
					goto reread;

				icmp = (struct icmp *)(buff + hlen);

				/* 檢查是否收到無關的封包 */
				if ((icmp->icmp_type != ICMP_TIMXCEED
							|| icmp->icmp_code != ICMP_TIMXCEED_INTRANS)
						&& (icmp->icmp_type != ICMP_UNREACH_PORT))
					goto reread;

				/* 記錄接收封包的時刻 */
				gettimeofday(&tvm1, (struct timezone *)0);
				tvsub(&tvm1, &tvm0);

				memcpy(&ipaddr, &(ip->ip_src.s_addr), sizeof ipaddr);
				strcpy(hostip, inet_ntoa(*(struct in_addr *) &(ip->ip_src.s_addr)));

				/* 顯示IP址與域名 */
				if (dns_flg == OFF) 
					printf("%-15s", hostip);
				else if ((host = gethostbyaddr((char *)&ipaddr, 4, AF_INET)) == NULL)
					printf("%-15s (%s) ", hostip, hostip);
				else 
					printf("%-15s (%s) ", hostip, host->h_name);

				printf(": RTT =%8.4f ms", tvm1.tv_sec*1000.0 + tvm1.tv_usec/1000.0);

				/* 檢查是否抵達目的主機 */
				if (icmp->icmp_type == ICMP_UNREACH_PORT) {
					printf("  Reach!\n");
					goto exit;
				} else
					break;
			} else {
				printf("? ");
				fflush(stdout);
			}
		}
		printf("\n");
	}
exit:
	close(send_sd);
	close(recv_sd);

	return EXIT_SUCCESS;
}

/* 
 * void make_udp_header(struct udphdr *udp);
 * 功能
 *     製作UDP起始碼
 * 自變數 
 *     struct udphdr *udp;  製作UDP起始碼的前端址
 * 返送值
 *     無
 */
void make_udp_header(struct udphdr *udp)
{
	udp->uh_sport = htons(0);
	udp->uh_ulen  = htons((u_short) sizeof(struct udphdr));
	udp->uh_dport = htons(33434); /* traceroute的埠號 */
	udp->uh_sum   = htons(0);
}

/* 
 * void make_ip_header(struct ip *ip, int srcip, int dstip, int iplen);
 * 功能
 *     製作IP起始碼
 * 自變數 
 *     struct ip *ip;  製作IP起始碼的前端址
 *     int srcip;      發送端IP址
 *     int dstip;      接收端IP址
 *     int iplen;      IP資料組的全長
 * 返送值
 *     無
 */
void make_ip_header(struct ip *ip, int srcip, int dstip, int iplen)
{
	memset((char *) ip, 0, sizeof(struct ip));

	/* 製作IP起始碼 */
	ip->ip_v   = IPVERSION;
	ip->ip_hl  = sizeof(struct ip) >> 2;
	ip->ip_id  = htons(0);
	ip->ip_off = 0;

#ifdef __linux
	/* Linux的Raw IP的時候 */
	ip->ip_len = htons(iplen);
	ip->ip_off = htons(0);
#else
	/* BSD的Raw IP的時候 */
	ip->ip_len = iplen;
	ip->ip_off = 0;
#endif
	ip->ip_ttl = 64;
	ip->ip_p   = IPPROTO_UDP;
	ip->ip_src.s_addr = srcip;
	ip->ip_dst.s_addr = dstip;

	/* 計算和核對 */
	ip->ip_sum = 0;
	ip->ip_sum = checksum((u_short *) ip, sizeof(struct ip));
}

/* 
 * void tvsub(struct timeval *out,struct timeval *in);
 * 功能
 *     struct timeval的減算。結果存儲於out上。
 * 自變數 
 *     struct timeval *out;  被減數
 *     struct timeval *in;   減數
 * 返送值
 *     無
 */
void tvsub(struct timeval *out, struct timeval *in)
{
	if ((out->tv_usec -= in->tv_usec) < 0) {
		out->tv_sec--;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}

/*
 * u_short checksum(u_short *data, int len);
 * 功能
 *     計算和核對
 * 自變數 
 *     u_short *data;   求取和核對資料
 *     int len;         資料的位元組數
 * 返送值
 *     u_short          和核對值（補數值）
 */
u_short checksum(u_short *data, int len)
{
	long sum = 0; /* 求取和核對 */

	/* 每兩個位元組相加 */
	for (; len > 1; len -=2) {
		sum += *data++;
		if (sum & 0x80000000) 
			sum = (sum & 0xffff) + (sum >> 16);
	}


	/* 資料長度為奇數位元組時之處理 */
	if (len == 1) {
		u_short i = 0;
		*(u_char*)(&i) = *(u_char *)data;
		sum += i;
	}

	/* 折返溢位 */
	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return ~sum;
}


