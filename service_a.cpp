#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>

int main()
{
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    int ch = 3;

    // tao socket cho trinh khach. luu lai so mo ta socket
    sockfd=socket(AF_UNIX,SOCK_STREAM,0);
    address.sun_family=AF_UNIX;
    // gan ten socket tren may chu can ket noi
    strcpy(address.sun_path,"server_socket");
    len =sizeof(address);
    // thu hien ket noi
    result = connect(sockfd,(struct sockaddr *)&address,len);
    if(result == -1)
    {
        perror("oops: client1 problem");
        exit(EXIT_FAILURE);
    }
    // sau khi ket noi, doc ghi du lieu nhu tren file
    write(sockfd, &ch,1);
    sleep(1);
    read(sockfd, &ch,1);
    printf("int from server = %d\n",ch);
    close(sockfd);
    exit(0);
}