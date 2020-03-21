#include<iostream>
//#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/ioctl.h>
#include<sys/epoll.h>
#include<arpa/inet.h>
#include<vector>
//#include<sys/socketvar.h>
//#include<fcntl.h>
#define SERV_PORT 8000
int main()
{
    std::cout<<"PID process server running: "<<(int)getpid()<<std::endl;
    int i,listenfd, connfd, sockfd;
    int n;
    std::vector<int> nosocket; 
    ssize_t nready, efd, res;
    char buff[1024], buffer[1024], str[INET_ADDRSTRLEN];
    socklen_t clilen;
    int client[65525];
    struct sockaddr_in cliaddr, servaddr;
    struct epoll_event tep, ep[65525];

    listenfd = socket(AF_INET,SOCK_STREAM, 0);
    //bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(SERV_PORT);
    bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    listen(listenfd,20);
    efd = epoll_create(65525);
    tep.events = EPOLLIN; tep.data.fd = listenfd;

    res = epoll_ctl(efd,EPOLL_CTL_ADD,listenfd,&tep);
    FILE *file = fopen("data.txt","w");
    if(file == NULL)
    {
        printf("Open file Error !!!");
        exit(1);
    }
    fclose(file);
    FILE *file2 = fopen("data2.txt","w");
    if(file2 == NULL)
    {
        printf("Open file Error !!!");
        exit(1);
    }
    fclose(file2);
    while(true)
    {
        printf("server waiting !!!\n");
        //
        nready = epoll_wait(efd,ep,65525,-1);
        
        for(i =0;i<nready;i++)
        {
            if(ep[i].data.fd == listenfd)
            {
                clilen = sizeof(cliaddr);
                connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen);
                nosocket.push_back(connfd);
                printf("received from %s at PORT %d\n",inet_ntop(AF_INET,&cliaddr.sin_addr,str,INET_ADDRSTRLEN),ntohs(cliaddr.sin_port));
                
                tep.events = EPOLLIN; tep.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd,&tep);

            }
            else
            {
                sockfd = ep[i].data.fd;
                /*int error = 0;
                socklen_t len = sizeof (error);
                getsockopt (sockfd, SOL_SOCKET, SO_KEEPALIVE, &error, &len);
                if(error != 0)
                {
                    epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
                    close(sockfd);
                    printf("client [%d] closed connection\n",sockfd);
                }*/
                
                //n = read(sockfd,buf,MAXLINE);
                ioctl(sockfd,FIONREAD,&n);
                if(n==0)
                {
                    res = epoll_ctl(efd,EPOLL_CTL_DEL,sockfd,NULL);
                    close(sockfd);
                    printf("client [%d] closed connection\n",sockfd);
                }
                //printf("check IP: %s\n",inet_ntop(AF_INET,&cliaddr.sin_addr,str,INET_ADDRSTRLEN));
                if(sockfd == nosocket[1])
                {
                    read(sockfd,buff,1024);
                    //ch=ch+1;
                    //write(client_sockfd,&ch,1);
                    
                    file = fopen("data.txt","a");
                    fprintf(file,"%s\n",buff);
                    fclose(file);
                    printf("Wrote %s from fd %d\n",buff,sockfd);
        
                }
                else if(sockfd == nosocket[0])
                {
                    read(sockfd,buffer,1024);
                    //ch=ch+1;
                    //write(client_sockfd,&ch,1);
                    
                    file2 = fopen("data2.txt","a");
                    fprintf(file2,"%s\n",buffer);
                    fclose(file2);
                    printf("Wrote %s from fd %d\n",buffer,sockfd);
                }
                
            }
            
        }
    }
}