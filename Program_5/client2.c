#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void str_cli(FILE *fp, int sockfd)
{
	int bufsize = 10240, cont;
	char *buffer = malloc(bufsize);
	while(1){	
	if((cont=recv(sockfd, buffer, bufsize, 0))>0) 
	{
		fputs("\nFriend:",stdout);
		fputs(buffer,stdout);
	}
	fputs("Me:",stdout);
	if(fgets(buffer,bufsize,fp)!=NULL)
	{
		send(sockfd, buffer, sizeof(buffer), 0);
	}}
	printf("\nEOF\n");
}
int main(int argc,char *argv[])
{
	int create_socket;
	struct sockaddr_in address;
	if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
		printf("The Socket was created\n");

	address.sin_family = AF_INET;
	address.sin_port = htons(16001);
	inet_pton(AF_INET,argv[1],&address.sin_addr);

	if (connect(create_socket,(struct sockaddr *) &address, sizeof(address)) == 0)
		printf("The connection was accepted with the server %s...\n",argv[1]);
	else
		printf("error in connect \n");

	str_cli(stdin, create_socket);
	return close(create_socket);
}
