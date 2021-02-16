#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc,char * argv[])
{
	int create_socket;
	char send1[150];
	struct sockaddr_in address;
	int bufsize=1024;
	char * buffer=malloc(bufsize);
	
	if((create_socket=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("Error while creating socket\n");
		exit(0);	
	}
	else
	{
		printf("Socket Created!\n");
	}
	address.sin_family = AF_INET;
	address.sin_port=htons(15000);
	inet_pton(AF_INET,argv[1],&address.sin_addr);
	if(connect(create_socket,(struct sockaddr *)&address,sizeof(address))<0)
	{
		printf("Error while connecting socket\n");
		exit(0);	
	}
	else
	{
		printf("Socket connected to %s..\n",argv[1]);
	}
	while(1)
	{
		printf("Enter command : ");
		gets(send1);
		if(strcmp(send1,"end")==0)
		{
			printf("sending command to server : ");
			send(create_socket,send1,50,0);
			break;
		}
		else
		{
			printf("sending command to server : ");	
			send(create_socket,send1,50,0);
		}
	}
	close(create_socket);
	return 0;
}




