#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void)
{
        int listenfd = 0,connfd = 0;

        struct sockaddr_in serv_addr;

        char sendBuff[1025];  
        int numrv;  

        listenfd = socket(AF_INET, SOCK_STREAM, 0);
        printf("socket retrieve success\n");

        memset(&serv_addr, '0', sizeof(serv_addr));
        memset(sendBuff, '0', sizeof(sendBuff));

        serv_addr.sin_family = AF_INET;    
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
        serv_addr.sin_port = htons(5000);    

        int ret = bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
        printf("%d\n", ret);

        if(listen(listenfd, 10) == -1){
                printf("Failed to listen\n");
                return -1;
        }


        while(1)
        {
                struct sockaddr addr;
                char ipstr[INET6_ADDRSTRLEN] = {'\0'};
                socklen_t len;
                connfd = accept(listenfd, (struct sockaddr*)&addr ,(socklen_t*)&len); // accept awaiting request
                struct sockaddr_in *s = (struct sockaddr_in *)&addr;
                int port = ntohs(s->sin_port);
                inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
                strcpy(sendBuff, "Message from server");
                write(connfd, sendBuff, strlen(sendBuff));

                close(connfd);    
                sleep(1);
        }


        return 0;
}
