// SERVER
// connect()
// fcntl
// inet_aton

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{

	int create_socket, open_fd, new_socket, fd,addrlen, count,cont;
	char fname[256];
	int bufsize = 1024;
	char *buffer = malloc(bufsize);
	char str[256] = "file not found!!!!";
	struct sockaddr_in address;

	// socket

	if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0)
		printf("socket created!\n");

	//bind
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(15000);
	if (bind(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0)
		// DON'T YOU DARE WRITE \N BEFORE STATEMENT STARTS
		printf("Binding socket\n");
	//listen
	listen(create_socket, 3);

	//accept
	addrlen = sizeof(struct sockaddr_in);

	new_socket = accept(create_socket, (struct sockaddr *)&address, &addrlen);
	if (new_socket > 0)
	{
		printf("socket accepted\n ");
		printf("client connected is %s\n ", inet_ntoa(address.sin_addr));
	}
	// recv fname
	recv(new_socket, fname, 255, 0);
	printf("file request recieved is : %s\n ", fname);

	// open file
	// DON'T FOEGET THE BRACKET
	if ((open_fd = open(fname, O_RDONLY)) < 0)
	{
		perror("File not found");
		write(new_socket, str, sizeof(str));
		exit(0);
	}
	// recv,send
		printf("Sending file details\n ");

	while ((count = read(open_fd, buffer, bufsize)) > 0)
	{
		//
		//printf("In while");
		send(new_socket, buffer, count, 0);
	}
	// close
	printf("Request Completed\n");
	close(new_socket);
	close(create_socket);
	return 0;
}
