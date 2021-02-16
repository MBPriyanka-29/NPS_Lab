/*Getservbyname program-  this program looks for the file /etc/services*/
/*The function returns a pointer to servent structure 

struct servent{
char *s_name;
char **s_aliases;
int s_port;
char *s_proto;
}

*/
#include <stdlib.h> 
#include <unistd.h> 
#include <errno.h> 
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include<stdio.h>
int main()
{
	struct servent* se;
	se = getservbyname("domain", "udp"); printf("ntohs : %d\n", ntohs(se->s_port)); 
printf(" s_name of domain : %s\n", se->s_name); 
 // when printing we can use htons but when storing this in structure, htons should not be used.
	se=getservbyname("ftp","tcp");printf("%d\n", htons(se->s_port));
    se=getservbyname("http","tcp");printf("%d\n", htons(se->s_port));
    se=getservbyname("telnet","tcp");printf("%d\n", htons(se->s_port));
    se=getservbyname("https","tcp");printf("%d\n", htons(se->s_port));
    se=getservbyname("daytime","tcp");printf("%d\n", htons(se->s_port));

se=getservbyname("echo","tcp");printf("%d\n", htons(se->s_port));
se=getservbyname("bootps","tcp");printf("%d\n", htons(se->s_port));//bootstrap

//Using getservbyport- Reverse of getservbyname
// The function prints the services offerred at the port.
 printf("Getservebyport function output\n");
    se=getservbyport(htons(53),NULL);  printf("%s\n",se->s_name);
	se=getservbyport(htons(21),"tcp");  printf("%s\n",se->s_name);
    se=getservbyport(htons(80),"tcp");  printf("%s\n",se->s_name);
	se=getservbyport(htons(23),"tcp");  printf("%s\n",se->s_name);
    se=getservbyport(htons(443),"tcp");  printf("%s\n",se->s_name);
    se=getservbyport(htons(13),"tcp");  printf("%s\n",se->s_name);

 se=getservbyport(htons(7),"tcp");  printf("%s\n",se->s_name);
 se=getservbyport(htons(67),"udp");  printf("%s\n",se->s_name);
 
}
