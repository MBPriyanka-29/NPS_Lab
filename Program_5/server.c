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

void str_echo(int connfd1, int connfd2)
{
	int n1,n2;
	int bufsize = 10240;
	char *buffer1 = malloc(bufsize);
	char *buffer2 = malloc(bufsize);
	while(1){
	if((n1=recv(connfd1, buffer1, bufsize, 0))>0) {
		fputs("client 1:",stdout);
		fputs(buffer1,stdout);
		send(connfd2, buffer1, sizeof(buffer1), 0);
		bzero(buffer1,10240);
	}
	if((n2=recv(connfd2, buffer2, bufsize, 0))>0){
		fputs("client 2:",stdout);
		fputs(buffer2,stdout);
		send(connfd1, buffer2, sizeof(buffer2), 0);
		bzero(buffer2,10240);
	}}
}

int main()
{
	int cont,listenfd,connfd1,connfd2,addrlen1,addrlen2,fd,pid,addrlen3;
	
	struct sockaddr_in address,cli_address1,cli_address2;
	if ((listenfd = socket(AF_INET,SOCK_STREAM,0)) > 0) 
	printf("The socket was created\n");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(16001);

	if (bind(listenfd,(struct sockaddr *)&address,sizeof(address)) ==0)
		printf("Binding Socket\n");
	printf("The address after bind %s ...\n",inet_ntoa(address.sin_addr) );

	listen(listenfd,3);
	printf("server is listening\n");

	getsockname(listenfd,(struct sockaddr *)&address,&addrlen3);
	printf("The server's local address %s ...and port %d\n",inet_ntoa(address.sin_addr),htons(address.sin_port));

	for(;;){
		addrlen1 = sizeof(struct sockaddr_in);
		connfd1 = accept(listenfd,(struct sockaddr *)&cli_address1,&addrlen1);
		addrlen2 = sizeof(struct sockaddr_in);
		connfd2 = accept(listenfd,(struct sockaddr *)&cli_address2,&addrlen2);
		printf("The Client %s is Connected...on port %d\n",inet_ntoa(cli_address1.sin_addr),htons(cli_address1.sin_port));
		printf("The Client %s is Connected...on port %d\n",inet_ntoa(cli_address2.sin_addr),htons(cli_address2.sin_port));

		str_echo(connfd1,connfd2);
		
	close(connfd1);
	close(connfd2);
	}
return 0 ;
}
