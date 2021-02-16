#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>

void str_echo(int fd,struct sockaddr * cli_addr,int clilen)
{	
	int n,r;
	int bufsize=1024;
	char * buffer=malloc(bufsize);
	struct sockaddr_in * client ;

	for(;;)
	{
	client = (struct sockaddr_in *)cli_addr;
	// recv from
	int addrlen = clilen;

	r=recvfrom(fd,buffer,bufsize,0,cli_addr,&clilen);
	printf("Client address %s and port %d\n",inet_ntoa(client->sin_addr),ntohs(client->sin_port));

	//sendto
	sendto(fd,buffer,r,0,cli_addr,clilen);
	printf("Echoing......\n");
	}
}
int main()
{

	int create_socket,addrlen,addrlen1,pid;
	
	struct sockaddr_in address,client;

	if((create_socket=socket(AF_INET,SOCK_DGRAM,0))>0)
	{
		printf("Socket created\n");	
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(15004);

	if(bind(create_socket,(struct sockaddr *)&address,sizeof(address))==0)
		printf("Binding socket!\n");
	
	str_echo(create_socket,(struct sockaddr *)&client,sizeof(client));
	exit(0);

	close(create_socket);
	return 0;
}

