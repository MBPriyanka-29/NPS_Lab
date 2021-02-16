#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>

void str_echo(int fd)
{	
	int bufsize=1024,r;
	char * buffer=malloc(bufsize);
again : while((r=recv(fd,buffer,bufsize,0))>0)
	{
		send(fd,buffer,r,0);
	}
	if(r<0)
		goto again;
}
int main()
{
	int create_socket,new_socket,addrlen,addrlen1,pid;
	int bufsize=1024;
	char * buffer=malloc(bufsize);
	struct sockaddr_in address;

	if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
	{
		printf("Socket created\n");	
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(15001);

	if(bind(create_socket,(struct sockaddr *)&address,sizeof(address))==0)
		printf("Binding socket!\n");
	listen(create_socket,3);

	for(;;)
	{
	addrlen=sizeof(struct sockaddr);
	addrlen1=sizeof(struct sockaddr);
	new_socket=accept(create_socket,(struct sockaddr *)&address,&addrlen);
	int i = getpeername(new_socket,(struct sockaddr *)&address,&addrlen1);
	printf("client connected : %s ip address with port %d \n",inet_ntoa(address.sin_addr),ntohs(address.sin_port));
	str_echo(new_socket);
	}
	close(new_socket);



	return 0;
}
