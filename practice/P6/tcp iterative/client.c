#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>

void str_echo(FILE *fp,int fd)
{

	int bufsize=1024,r;
	char * buffer=malloc(bufsize);
	while(fgets(buffer,bufsize,fp)!=NULL)
	{

		printf("\n Enter the string : ");
		printf("Sending to server..\n");
		send(fd,buffer,sizeof(buffer),0);
		if((r=recv(fd,buffer,sizeof(buffer),0))>0)
		{
			printf("Echoed msg : ");
			fputs(buffer,stdout);
			printf("\n");
		}

	}
}

int main(int argc,char * argv[])
{
	int create_socket;
	int bufsize=1024;
	char * buffer=malloc(bufsize);
	struct sockaddr_in address;

	if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
	{
		printf("Socket created\n");	
	}
	address.sin_family = AF_INET;
	inet_pton(AF_INET,argv[1],&address.sin_addr);
	address.sin_port = htons(15001);

	if(connect(create_socket,(struct sockaddr *)&address,sizeof(address))==0)
		printf("Connecting socket!\n");
	str_echo(stdin,create_socket);
	close(create_socket);
	return 0;
}
