/*******************************************************/
/* Network Time Protocol                               */
/* ntp.c                                               */
/*                                                     */
/* Program skeleton :                                  */
/* >system>sample_programs>tcp_os>simple_tcp_connect.c */
/*                                                     */
/* PRIMITIVE implementation                            */
/*                                                     */
/* Parameters                                          */
/* ----------                                          */
/*                                                     */
/* time_server        : ip address of a time server    */
/* set_vos_time       : flag indicates whether program */
/*                      will set the date and time     */
/* minutes_difference : difference in minutes between  */
/*                      the module's time and GMT      */
/*                                                     */
/* Some time serverz below                             */
/* -----------------------                             */
/* ben.cs.wisc.edu (128.105.201.11)                    */
/* bigben.cac.washington.edu (140.142.16.34)           */
/* bitsy.mit.edu (18.72.0.3)                           */
/* canon.inria.fr (192.93.2.20)                        */
/* chronos.univ-rennes1.fr (129.20.128.2)              */
/* clepsydra.dec.com (16.1.0.4, 204.123.2.5)           */
/* clock.nc.fukuoka-u.ac.jp (133.100.9.2)              */
/*                                                     */
/* More info: http://www.eecis.udel.edu/~ntp/          */
/*                                                     */
/* NTG                                                 */
/*******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <tcp_socket.h>

#define CV char_varying
#define DEF_PROTOCOL 0
#define FLAG_BITS    0
#define BUFSIZE 4096

union decimal_15_tag
{
	struct $shortmap
	{
		short int           pad;
		unsigned long int   high;
		unsigned short int  low;
	};
	double for_alignment_only;
}

main()
{
	short               error_code;
	CV(256)             v_iaddress;
	char                iaddress[256];
	int                 sd;
	struct sockaddr     bind_saddr;
	struct sockaddr_in  *sin;
	int                 rval;
	short               msg_size = 100;
	char                recv_buf[BUFSIZE];

	short               set_flag;
	short               min_diff;
	long int            ss_time;
	CV(256)             vos_date_time_str;
	long int            delta_secs;
	union decimal_15_tag jiffy_date_time;

	/* Get parameters */
	strcpy(v_iaddress,"130.88.202.49");
	s$parse_command(&(CV(32))"Network Time Protocol", &error_code,
			&(CV)"option(-time_server),string,req,='130.88.202.49'",&v_iaddress,
			&(CV)"switch(-set_vos_time),=0",&set_flag,
			&(CV)"option(-minutes_difference),number,word,req,=120",&min_diff,
			&(CV)"end");
	if (error_code != 0)
		return;
	strcpy(iaddress, v_iaddress);
	/* start connection */
	sd = socket(AF_INET, SOCK_STREAM, DEF_PROTOCOL);
	if (sd < 0)
		example_exit("Error on socket()");
	sin = (struct sockaddr_in *)&bind_saddr;
	sin->sin_family = AF_INET;
	sin->sin_port = 13;  /* ntp is on port 13 */
	sin->sin_addr.s_addr = inet_addr(iaddress);
	if (sin->sin_addr.s_addr == -1)
		example_exit("Improper connect address");
	rval = connect(sd, &bind_saddr, sizeof(bind_saddr));
	if (rval < 0)
		example_exit("Error on connect()");
	rval = recv(sd, &recv_buf[0], msg_size, FLAG_BITS);
	if (rval <= 0)
		example_exit("Error on recv()");
	shutdown(sd, READ_WRITE_SHUTDOWN);
	net_close(sd);
	/* We have string from time server, piece it together */
	printf("Time server string : %s\n",recv_buf);
	if (set_flag != 0)
	{
		strcpy(vos_date_time_str,$substr(recv_buf,5,3));
		strcat(vos_date_time_str," ");
		strcat(vos_date_time_str,$substr(recv_buf,9,2));
		strcat(vos_date_time_str,",");
		strcat(vos_date_time_str,$substr(recv_buf,21,4));
		strcat(vos_date_time_str," ");
		strcat(vos_date_time_str,$substr(recv_buf,12,8));
		/* this string -> system time */
		s$cv_to_int_date_time(&vos_date_time_str,
				&ss_time,
				&error_code);
		if (error_code != 0) {
			s$error(&error_code,
					&(CV)"NTP",
					&(CV)" - from s$cv_to_int_date_time");
			return;
		}
		/* calculate offset in seconds */
		delta_secs = min_diff * 60;
		ss_time = ss_time + delta_secs;
		/* get time now in jiffies */
		s$jiffy_date_time(&jiffy_date_time);
		/* set new time in jiffies */
		jiffy_date_time.high = ss_time;
		jiffy_date_time.low = 0;
		s$set_jiffy_date_time(&jiffy_date_time);
	}
}

example_exit (exit_str)
	char *exit_str;
{
	perror(exit_str);
	exit(1);
}
