
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include<stdlib.h>
#define GROUP "225.0.0.37"
#define PORT 12345

int main(int argc,char * argv[])
{
	int create_socket;
	struct sockaddr_in address;
	char * msg="HEY YOU!";
	// socket
	if((create_socket=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
	printf("Error while creating socket");
	exit(0);
	}
	// memset
	//memset(&address,0,sizeof(address));
	// set up destination
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr(GROUP);
	address.sin_port=htons(PORT);

	//while(1) : sendto,sleep
	while(1)
	{
	if(sendto(create_socket,msg,sizeof(msg),0,(struct sockaddr *)&address,sizeof(address))<0)
	{
		printf("error while sending!");
		exit(0);
	}
	sleep(1);
	}
}
