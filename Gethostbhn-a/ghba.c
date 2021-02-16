/* Gethostbyaddr*/
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
int main() 
{ 
    char hname[256]; 
    char *IPaddr; 
    struct hostent *hptr; 
struct in_addr addr;
    int hostname; 
  
 
      
    //retrieve host information 
   if((hptr = gethostbyname("www.netflix.com"))==NULL)
      {
		printf("Error"); 
        exit(0);
	  }
  
    // To convert an Internet networkaddress into ASCII string 
    IPaddr = inet_ntoa(*((struct in_addr*)hptr->h_addr_list[0])); 
    // COntents of hostent structure   
    printf("Host IP: %s\n", IPaddr); 
	printf("Hostname :%s\n",hptr->h_name);
    printf("Hostname aliases:%s\n",hptr->h_aliases[0]);
	printf("Hostname aliases1:%s\n",hptr->h_aliases[1]);
    printf("Hostname aliases2:%s\n",hptr->h_aliases[2]);
    printf("Address Type:%d\n",hptr->h_addrtype);
	printf("Address Length:%d\n",hptr->h_length);
    
    inet_aton("192.168.43.9", &addr); // my laptop ip address

    hptr=gethostbyaddr(&addr, sizeof(addr),AF_INET);
    printf("Host name from gethostbyaddr: %s \n", hptr->h_name);

    return 0; 
} 
