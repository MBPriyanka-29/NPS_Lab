#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<string.h>

void str_client(FILE *fp,int fd)
{
	int bufsize=1024,count;
	char * buffer=malloc(bufsize);
	
	// friend : recv,fputs
	while(1)
	{
	if((count=recv(fd,buffer,bufsize,0))>0)
	{
	fputs("Friend : ",stdout);
	fputs(buffer,stdout);
	}
	// me : fputs
	fputs("Me :",stdout);
	
	// if fgets not null, send
	if(fgets(buffer,bufsize,fp)!=NULL)
		send(fd,buffer,sizeof(buffer),0);
	}
}
int main(int argc,char * argv[])
{
	int addrlen1,addrlen2,addrlen3,create_socket,confd1,confd2;
	struct sockaddr_in address,client1_address,client2_address;
	// str_client(stdout,create_socket)
	//close
	
	// socket
	if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
		printf("Socket created!\n");
	
	// connect
	address.sin_family=AF_INET;
	address.sin_port=htons(15000);
	inet_pton(AF_INET,argv[1],&address.sin_addr);
	if(connect(create_socket,(struct sockaddr *)&address,sizeof(address))==0)
		printf("Socket connected to %s..\n",argv[1]);
	else
		printf("ERROR IN CONNECT");
	printf("Client2!!\n");
	str_client(stdin,create_socket);
	//close
	close(create_socket);
	return 0;
}




