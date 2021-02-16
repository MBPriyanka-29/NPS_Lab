#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include <arpa/inet.h>

void str_echo(FILE * fp,int fd,struct sockaddr * serv_addr,int servlen)
{	
	int n,r;
	int bufsize=1024;
	char * buffer=malloc(bufsize);
	int len=sizeof(struct sockaddr_in);
	
	struct sockaddr_in * pre_reply;
	
	if(fgets(buffer,bufsize,fp)!=NULL)
	{
	//sendto
	sendto(fd,buffer,sizeof(buffer),0,serv_addr,servlen);
	// recvfrom
	printf("Sending %s\n",buffer);
	if((r=recvfrom(fd,buffer,bufsize,0,(struct sockaddr *)pre_reply,&len))>0)
	{
		printf("Message recived : ");
		fputs(buffer,stdout);
		printf("\n");
	}
	
	}
	
}
int main(int argc, char * argv[])
{

	int create_socket,servlen;

	
	struct sockaddr_in serv;

	if((create_socket=socket(AF_INET,SOCK_DGRAM,0))>0)
	{
		printf("Socket created\n");	
	}
	
	serv.sin_family = AF_INET;
	inet_pton(AF_INET,argv[1],&serv.sin_addr);
	serv.sin_port = htons(15004);
	
	str_echo(stdin,create_socket,(struct sockaddr *)&serv,sizeof(serv)); // send sizeof
	
	// VERY IMP
	exit(0);
	
	close(create_socket);
	return 0;
}

