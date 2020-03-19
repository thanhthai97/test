//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/epoll.h>
//#include<errno.h>
#include<sys/socket.h>
#include<unistd.h>
#include<iostream>
#include<sys/ioctl.h>

#define MAXLINE 80
#define SERV_PORT 8000
#define OPEN_MAX 65525

int main(int argc, char *argv[])
{
    int i,listenfd, connfd, sockfd;
    int n;
    ssize_t nready, efd, res;
    char ch, str[INET_ADDRSTRLEN];
    socklen_t clilen;
    int client[OPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;
    struct epoll_event tep, ep[OPEN_MAX];

    listenfd = socket(AF_INET,SOCK_STREAM, 0);
    //bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    listen(listenfd,20);
    efd = epoll_create(OPEN_MAX);
    tep.events = EPOLLIN; tep.data.fd = listenfd;

    res = epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep);

    while(true)
    {
        printf("server waiting ....\n");
        nready = epoll_wait(efd,ep,OPEN_MAX,-1);
        
        for(i =0;i<nready;i++)
        {
            if(ep[i].data.fd == listenfd)
            {
                clilen = sizeof(cliaddr);
                connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);

                printf("received from %s at PORT %d\n",inet_ntop(AF_INET,&cliaddr.sin_addr,str,INET_ADDRSTRLEN),ntohs(cliaddr.sin_port));

                tep.events = EPOLLIN; tep.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd,&tep);

            }
            else
            {
                sockfd = ep[i].data.fd;
                //n = read(sockfd,buf,MAXLINE);
                /*ioctl(sockfd,FIONREAD,&n);
                if(n==0)
                {
                    res = epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
                    close(sockfd);
                    printf("client [%d] closed connection\n",sockfd);

                }
                else*/
                {
                    /* code */
                    /*for(j=0;j<n;j++)
                    {
                        buf[j]=toupper(buf[j]);
                        write(sockfd,buf,n);
                    }*/
                    read(sockfd,&ch,1);
                    printf("server client on %d\n",sockfd);
                    ch++;
                    write(sockfd,&ch,1);
                }
                
            }
            
        }
    }    
}