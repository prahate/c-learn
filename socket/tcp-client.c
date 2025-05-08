#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/***
 * To test open another terminal and run nc command
 *
 * nc -l -p 32678
 *
 * */


#define MYPORT 32678

int main()
{
	int sockfd;
	int status;
	struct sockaddr_in myaddr;
	char text[256], recv_text[256];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("socket");
		return -1;
	}

	memset(&myaddr, 0, sizeof(myaddr)); 
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(MYPORT);
	inet_aton("127.0.0.1", &myaddr.sin_addr);

	status = connect(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr));
	if (status < 0) {
		perror("connect");
		close(sockfd);
		return status;
	}
	
	sprintf(text, "hello there, server !!!!,from client with love\n");

	send(sockfd, text, strlen(text), 0);

	status = recv(sockfd, recv_text, sizeof(recv_text),0);
	if (status > 0)
		printf("Received %s\n", recv_text);

	close(sockfd);
	return 0;
}
