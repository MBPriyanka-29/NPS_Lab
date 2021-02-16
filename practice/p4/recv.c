
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
#define msgbufsize 25
int main(int argc,char * argv[])
{

	int create_socket,addrlen,r;
	struct sockaddr_in address;
	char msg[msgbufsize];

	// IP_MREQ !!!!!!!!!!!!!!!!
	struct ip_mreq mreq;
	u_int yes=1;
	// socket
	if((create_socket=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		printf("\nError while creating socket");
		exit(0);
	}
	
	//memset(&address,0,sizeof(address));

	// set up destination
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=INADDR_ANY;
	address.sin_port=htons(PORT);
	//bind
	if(bind(create_socket,(struct sockaddr *)&address,sizeof(address))<0)
		printf("\nSError binding!");
	//make port reusable
	
	if(setsockopt(create_socket,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes))<0)
		printf("Reuse error!");
		
	//mreq initialisation
	// IMR_MULTIADDR !!!!!
	// IMR_INTERFACE !!!!!!!!
	mreq.imr_multiaddr.s_addr=inet_addr(GROUP);
	mreq.imr_interface.s_addr=INADDR_ANY;
	// membership

	// IPPROTO_IP !!!!!!!!!!
	// UP_ADD_MEMBERSHIP !!!!!!!!!!!!!!
	if(setsockopt(create_socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq))<0)
		printf("setsock error!");
	//while(1) : recvfrom,puts

	while(1)
	{
		addrlen=sizeof(struct sockaddr_in);
		if((r=recvfrom(create_socket,msg,sizeof(msg),0,(struct sockaddr *)&address,&addrlen))<0)
		{
			printf("error while recieving!");
			exit(0);
		}
		puts(msg);

	}
}
