#include<iostream>
#include<sys/epoll.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>

int main()
{
    int lfd, cfd, efd;
    struct sockaddr_in  server_address,client_address;
    socklen_t client_len;
    char buff[1024];
    int len,n;
    struct epoll_event tep, ep[1024];

    lfd = socket(AF_INET,SOCK_STREAM,0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8080);

    bind(lfd, (struct sockaddr *)&server_address,sizeof(server_address));

    listen(lfd,5);
    // Init epoll
    efd = epoll_create(1024);

    tep.events = EPOLLIN;
    tep.data.fd = lfd;
    epoll_ctl(efd,EPOLL_CTL_ADD, lfd,&tep);
    while(true)
    {
        n = epoll_wait(efd,ep,1024,-1);
        for(int i =0;i<n;i++)
        {
            client_len = sizeof(client_address);

            cfd = accept(lfd,(struct sockaddr *)&client_address,(socklen_t*)client_len);

             len = read(cfd,buff,sizeof(buff));
        }
        write(lfd,buff,sizeof(buff));
    }
    close(lfd);
    close(cfd);

}