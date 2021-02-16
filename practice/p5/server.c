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

void str_echo(int confd1,int confd2)
{
	int count1,count2;
	// buffer1,bufsize1
	//buffer2,bufsize2
	int bufsize1=1024;
	int bufsize2=1024;
	char *buffer1=malloc(bufsize1);
	char *buffer2=malloc(bufsize2);

	// recv from client1, send it to client2
	
	// ITS A INFINITE WHILE
	
	while(1){
	
	// ITS AN IF !!!!!!!!!!!!
	
	if((count1=recv(confd1,buffer1,bufsize1,0))>0)
	{
	fputs("client1 : ",stdout);
	fputs(buffer1,stdout);
	send(confd2,buffer1,count1,0);
	bzero(buffer1,10240);
	}
	
	//recv from client2, send it to client1
	
	if((count2=recv(confd2,buffer2,count2,0))>0)
	{
	fputs("client2 : ",stdout);
	fputs(buffer2,stdout);
	send(confd1,buffer2,count2,0);
	bzero(buffer1,10240);

	}}
}

int main()
{
	int addrlen1,addrlen2,addrlen3,create_socket,confd1,confd2;
	struct sockaddr_in address,client1_address,client2_address;
	
	// socket
	if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
		printf("Socket created!\n");
	// bind
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	address.sin_port=htons(15000);
	if(bind(create_socket,(struct sockaddr *)&address,sizeof(address))==0)
		printf("Binding Socket!\n");
		
	// listen
	listen(create_socket,3);
	
	// accept in for loop

	getsockname(create_socket,(struct sockaddr *)&address,&addrlen3);
	printf("Connected to server %s with port %d \n",inet_ntoa(address.sin_addr),ntohs(address.sin_port));
	for(;;)
	{
		addrlen1=sizeof(struct sockaddr_in);
		confd1=accept(create_socket,(struct sockaddr *)&client1_address,&addrlen1);
		addrlen2=sizeof(struct sockaddr_in);
		confd2=accept(create_socket,(struct sockaddr *)&client2_address,&addrlen2);
		str_echo(confd1,confd2);
	}
	//close
	close(confd1);
	close(confd2);
	close(create_socket);
	return 0;
}
