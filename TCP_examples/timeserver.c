#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>                                        
#include<fcntl.h>
#include<arpa/inet.h>
#include<string.h>
#include<time.h>
int main()
{
  int cont, create_socket,new_socket,addr_len,fd,connfd,len;
  char fname[256];
  time_t ticks;
  struct sockaddr_in address,cliaddr;
   if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
   printf("The socket is created\n");
   address.sin_family=AF_INET;
   address.sin_addr.s_addr=INADDR_ANY;
   address.sin_port=htons(15000);
 
  if(bind(create_socket,(struct sockaddr *)&address,sizeof(address))==0)
   printf("Binding Socket\n");
  listen(create_socket,4);
 getsockname(create_socket, (struct sockaddr*)&address, &len);                  
 printf("The Server %s is connected binded at port no %d \n",  inet_ntoa(address.sin_addr), htons(address.sin_port));
  
	for ( ; ; )    {
			 len=sizeof(cliaddr);
			 connfd=accept(create_socket, (struct sockaddr*)&cliaddr,&len);
			 //printf("the client  %s is connected \n",  inet_ntoa(cliaddr.sin_addr));
			 getpeername(connfd, (struct sockaddr*)&cliaddr, &len);                       
			 printf("The client's IP address is  %s and port number is %d \n",  inet_ntoa(cliaddr.sin_addr),htons(cliaddr.sin_port));
			 ntohs(cliaddr.sin_port);
			 ticks=time(&ticks);
			 snprintf(fname,sizeof(fname), "Current Time is = %s",ctime(&ticks));
			 send(connfd,fname,37,0);			 
			 printf("Current time = %s", ctime(&ticks));
			 close(connfd);
		      }
	close(create_socket);
}

