#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main()
{
    // socket file descriptor
    int sockfd, new_socket, c;
    struct sockaddr_in name, client;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
	bzero(&name, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_port = htons(8080);
    name.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *) &name, sizeof(name)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    listen(sockfd, 3);
    printf("socket created!");
    //Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	new_socket = accept(sockfd, (struct sockaddr *)&client, (socklen_t*)&c);
	if (new_socket<0)
	{
		perror("accept failed");
	}

	puts("Connection accepted");
}
