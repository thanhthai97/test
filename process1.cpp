#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<unistd.h>
#include<random>
#include<time.h>
#include<pthread.h>

void sleep(int &ssecond)
{
    struct timespec ts = {ssecond,0};
    nanosleep(&ts,NULL);
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
    while(true){
    pthread_mutex_lock(&sum_lock);
    int sockfd;
    int len;
    struct sockaddr_un address;
    int result;
    //int ch = 3;

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
    write(sockfd, &sum,1);
    //read(sockfd, &ch,1);
    printf("write on server %d\n",sum);
    close(sockfd);
    pthread_mutex_unlock(&sum_lock);
    sleep(5);
    }
}

int main()
{
   std::cout<<"Ma tien trinh dang chay: "<<(int)getpid()<<std::endl;
   pthread_t a_thread;
   pthread_t b_thread;
   pthread_t c_thread;
   void *thread_result;
   int thread_num;
   // Khoi tao mutex
   thread_num=pthread_mutex_init(&sum_lock,NULL);
   if(thread_num!=0)
   {
       perror("Thread mutex created error");
       exit(EXIT_FAILURE);
   }
   // tao tuyen thu ba
   thread_num=pthread_create(&c_thread,NULL,thread_3,NULL);
   if(thread_num!=0)
   {
       perror("Thread3 created error");
       exit(EXIT_FAILURE);
   }
   // tao tuyen thu hai
   thread_num=pthread_create(&b_thread,NULL,thread_2,NULL);
   if(thread_num!=0)
   {
       perror("Thread2 created error");
       exit(EXIT_FAILURE);
   }
   //tao tuyen thu nhat
   thread_num=pthread_create(&a_thread,NULL,thread_1,NULL);
   if(thread_num!=0)
   {
       perror("Thread2 created error");
       exit(EXIT_FAILURE);
   }
   
   // Huy tuyen
   pthread_join(a_thread,&thread_result);
   pthread_join(b_thread,&thread_result);
   pthread_join(c_thread,&thread_result);
   // Huy mutex
   pthread_mutex_destroy(&sum_lock);
    
}