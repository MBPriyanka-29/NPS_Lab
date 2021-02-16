// CLIENT
// connect()
// fcntl
// inet_aton

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>

#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc,char * argv[])
{

int create_socket,count,cont;
struct sockaddr_in address;
char fname[256];
int bufsize = 1024;
char *buffer=malloc(bufsize);

// socket
if((create_socket=socket(AF_INET,SOCK_STREAM,0))>0)
	printf("socket created!\n");

//connect
address.sin_family = AF_INET;
address.sin_port = htons(15000);

// AGAIN!!! DONT FORGET THIS
// DONT BE STUPID AND USE INADDR_ANY!!!!!!!!!!
inet_pton(AF_INET,argv[1],&address.sin_addr);

if((connect(create_socket,(struct sockaddr *)&address,sizeof(address)))==0)
	printf("socket connected!\n");
	
// take filename from user
printf("Enter file name : ");
scanf("%s",fname);

printf("File name entered is : %s \n ",fname);
// send file name to server
printf("sending file name to server...\n ");
send(create_socket,fname,sizeof(fname),0);

printf("Details in file as recieved from server : \n");
// recv,write on terminal
while((count=recv(create_socket,buffer,bufsize,0))>0)
{
printf("Recieving");
write(1,buffer,count);
}
// close
  printf("\nEOF\n");

close(create_socket);
return 0;
}
