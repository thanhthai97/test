#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<random>
#include<sys/time.h>
#include<pthread.h>
#include<arpa/inet.h>
//#include<string.h>
//#include<stdio.h>
//#include<stdlib.h>

/*void sleep(int &ssecond)
{
    struct timespec ts = {ssecond,0};
    nanosleep(&ts,NULL);
}*/
void reverse(char str[], int length) 
{ 
    int start = 0; 
    int end = length -1; 
    while (start < end) 
    { 
        std::swap(*(str+start), *(str+end)); 
        start++; 
        end--; 
    } 
}  

char* itoa(int num, char* str, int base) 
{ 
    int i = 0; 
    bool isNegative = false; 
  
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0) 
    { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        return str; 
    } 
  
    // In standard itoa(), negative numbers are handled only with  
    // base 10. Otherwise numbers are considered unsigned. 
    if (num < 0 && base == 10) 
    { 
        isNegative = true; 
        num = -num; 
    } 
  
    // Process individual digits 
    while (num != 0) 
    { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
  
    // If number is negative, append '-' 
    if (isNegative) 
        str[i++] = '-'; 
  
    str[i] = '\0'; // Append string terminator 
  
    // Reverse the string 
    reverse(str, i); 
  
    return str; 
} 

int data[2]={0,0};
pthread_mutex_t sum_lock;

int sum=0;
void *thread_1(void *arg)
{
    
    while(true){
        pthread_mutex_lock(&sum_lock);
        sum += (rand()%10 +1);
        std::cout<<"Sum hien tai = "<<sum<<std::endl;
       
        pthread_mutex_unlock(&sum_lock);
        sleep(1); 
   }
}
    
    

void *thread_2(void *arg)
{
    
    //for(int n=0;n<4;n++){
    //
    while(true){
    //int value = sum;
    pthread_mutex_lock(&sum_lock);
    data[0]=data[1];
    data[1]=sum;
    std::cout<<"Average = "<<(double)(data[1]-data[0])/5<<std::endl;
    pthread_mutex_unlock(&sum_lock);
    sleep(5);
    }
    
}
void *thread_3(void *arg)
{
    
    
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    //int ch = 3;

    // tao socket cho trinh khach. luu lai so mo ta socket
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(8000);
    // gan ten socket tren may chu can ket noi
    //strcpy(address.sun_path,"server_socket");
    len =sizeof(address);
    // thu hien ket noi
    result = connect(sockfd,(struct sockaddr *)&address,len);
    if(result == -1)
    {
        perror("oops: client1 problem");
        exit(EXIT_FAILURE);
    }
    // sau khi ket noi, doc ghi du lieu nhu tren file
    char buff[1024];
    while(true){
        
    pthread_mutex_lock(&sum_lock);
    itoa(sum,buff,10);
    write(sockfd, buff,sizeof(buff));
    //read(sockfd, &ch,1);
    printf("thread 3 write on server %d\n",sum);
    
    pthread_mutex_unlock(&sum_lock);
    sleep(5);
    }
    close(sockfd);
}

void *thread_4(void *arg)
{
    
    //pthread_mutex_lock(&sum_lock);
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    //int ch = 3;

    // tao socket cho trinh khach. luu lai so mo ta socket
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr = inet_addr("192.168.81.12");
    address.sin_port = htons(8000);
    // gan ten socket tren may chu can ket noi
    //strcpy(address.sun_path,"server_socket");
    len = sizeof(address);
    // thu hien ket noi
    result = connect(sockfd,(struct sockaddr *)&address,len);
    if(result == -1)
    {
        perror("oops: client2 problem");
        exit(EXIT_FAILURE);
    }
    // sau khi ket noi, doc ghi du lieu nhu tren file
    char buffer[1024];
    while(true){
        
    int ran100 = rand()%100 +1;
    
    itoa(ran100,buffer,10);
    write(sockfd, buffer,sizeof(buffer));
    //read(sockfd, &ch,1);
    printf("thread 4 write on server %d\n",ran100);
    
    //pthread_mutex_unlock(&sum_lock);
    sleep(1);
    }
    close(sockfd);
}

int main()
{
   std::cout<<"PID process client running: "<<(int)getpid()<<std::endl;
   pthread_t a_thread;
   pthread_t b_thread;
   pthread_t c_thread;
   pthread_t d_thread;
   void *thread_result;
   int thread_num;
   // Khoi tao mutex
   thread_num=pthread_mutex_init(&sum_lock,NULL);
   if(thread_num!=0)
   {
       perror("Thread mutex created error");
       exit(EXIT_FAILURE);
   }
   // create thread 4
   thread_num=pthread_create(&d_thread,NULL,thread_4,NULL);
   if(thread_num!=0)
   {
       perror("Thread 4 created error");
       exit(EXIT_FAILURE);
   }
   // tao tuyen thu ba
   thread_num=pthread_create(&c_thread,NULL,thread_3,NULL);
   if(thread_num!=0)
   {
       perror("Thread 3 created error");
       exit(EXIT_FAILURE);
   }
   // tao tuyen thu hai
   thread_num=pthread_create(&b_thread,NULL,thread_2,NULL);
   if(thread_num!=0)
   {
       perror("Thread 2 created error");
       exit(EXIT_FAILURE);
   }
   //tao tuyen thu nhat
   thread_num=pthread_create(&a_thread,NULL,thread_1,NULL);
   if(thread_num!=0)
   {
       perror("Thread 1 created error");
       exit(EXIT_FAILURE);
   }
   
   // Huy tuyen
   pthread_join(a_thread,&thread_result);
   pthread_join(b_thread,&thread_result);
   pthread_join(c_thread,&thread_result);
   pthread_join(d_thread,&thread_result);
   // Huy mutex
   pthread_mutex_destroy(&sum_lock);
    
}