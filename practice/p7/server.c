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

int main()
{
	int create_socket,new_socket,addrlen,bytes;
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
	address.sin_addr.s_addr=INADDR_ANY;
	address.sin_port=htons(15000);
	
	if(bind(create_socket,(struct sockaddr *)&address,sizeof(address))<0)
	{
		printf("Error while binding socket\n");
		exit(0);	
	}
	else
	{
		printf("Socket binded!\n");
	}
	if(listen(create_socket,3)<0)
	{
		printf("Error while listening to socket\n");
		exit(0);	
	}
	else
	{
		printf("Socket is listening!\n");
	}
	addrlen=sizeof(struct sockaddr);
	if((new_socket=accept(create_socket,(struct sockaddr *)&address,&addrlen))<0)
	{
		printf("Error while accepting\n");
		exit(0);	
	}
	else
	{
		printf("Socket accepted!\n");
	}
	while(1)
	{
		bytes=recv(new_socket,buffer,bufsize,0);
		buffer[bytes]='\0';
		if(strcmp(buffer,"end")==0)
		{
			close(new_socket);
			close(create_socket);
			exit(0);
		}
		else
		{	
			printf("Recived command is : ");
			printf("%s\n",buffer);
			system(buffer);
			printf("\n");
		}
	}
	return 0;
}




