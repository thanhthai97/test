#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char ch = 'F';
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port=htons(8000);
    len =sizeof(address);
    // thu hien ket noi
    result = connect(sockfd,(struct sockaddr *)&address,len);
    if(result == -1)
    {
        perror("oops: client1 problem");
        exit(EXIT_FAILURE);
    }
    while(1){
    
    // sau khi ket noi, doc ghi du lieu nhu tren file
    write(sockfd, &ch,1);
    //send(sockfd,&,sizeof(ch),0);
    //sleep(1);
    read(sockfd, &ch,1);
    //recv(sockfd,&ch,sizeof(ch),0);
    printf("from server = %c\n",ch);
    sleep(2);
    }
    close(sockfd);
    //exit(0);
}