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
 * nc 127.0.0.01 32678
 *
 * */


#define MYPORT 32678

int main()
{
	int sockfd, clientfd, opt=1;
	int status;
	struct sockaddr_in myaddr, client_addr ;
	char text[256], recv_text[256];
	socklen_t addr_len = sizeof(client_addr);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("socket");
		return -1;
	}

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	memset(&myaddr, 0, sizeof(myaddr)); 
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(MYPORT);
	myaddr.sin_addr.s_addr = INADDR_ANY;

	status = bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr));
	if (status) {
		perror("bind");
		close(sockfd);
		return status;
	}

	status = listen(sockfd, 1);
	if (status) {
		perror("listen");
		close(sockfd);
		return status;
	}

	clientfd = accept(sockfd, (struct sockaddr *) &client_addr, &addr_len);
	if (clientfd < 0) {
		perror("accept");
		close(sockfd);
		return status;
	}
		
	printf("Server: client port %x, client address %s\n", client_addr.sin_port,
			inet_ntoa(client_addr.sin_addr));

	status = recv(clientfd, recv_text, sizeof(recv_text),0);
	if (status > 0)
		printf("Received: %s\n", recv_text);

	sprintf(text, "Server: Nice to see you client\n");
	send(clientfd, text, strlen(text), 0);


	close(clientfd);
	close(sockfd);
	return 0;
}
