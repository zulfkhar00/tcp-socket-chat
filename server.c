#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdlib.h>

#define PORT 6000
#define MAX_MSG_LEN 1024

void handle_client(int client_socket, struct sockaddr_in client_address)
{
	char buffer[MAX_MSG_LEN];
	int msg_len;
	while ((msg_len = recv(client_socket, buffer, MAX_MSG_LEN, 0)) > 0)
	{
		buffer[msg_len] = '\0';
		printf("[%s:%d] Received message: %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), buffer);
		if (strcmp(buffer, "BYE!") == 0 || msg_len == 0)
		{
			break;
		}
		printf("[%s:%d] Send message: %s\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port), buffer);
		send(client_socket, buffer, msg_len, 0);
	}
	close(client_socket);
	printf("[%s:%d] Disconnected\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
}

int main()
{
	struct sockaddr_in client_address;
	int addrlen = sizeof(client_address);
	// socket
	int server_sd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sd < 0)
	{
		perror("socket:");
		exit(-1);
	}
	// setsock
	int value = 1;
	setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)); //&(int){1},sizeof(int)
	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// bind
	if (bind(server_sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("bind failed");
		exit(-1);
	}
	// listen
	if (listen(server_sd, 5) < 0)
	{
		perror("listen failed");
		close(server_sd);
		exit(-1);
	}

	while (1)
	{
		// accept
		int client_sd = accept(server_sd, (struct sockaddr *)&client_address, (socklen_t *)&addrlen);
		if (client_sd < 0)
		{
			printf("Failed to accept client connection\n");
			continue;
		}
		printf("[%s:%d] Connected\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));
		int pid = fork(); // fork a child process
		if (pid == 0)	  // if it is the child process
		{
			close(server_sd);
			handle_client(client_sd, client_address);
			exit(EXIT_SUCCESS);
		}
		else if (pid < 0) // if we couldn't create child process
		{
			printf("Failed to create child process\n");
			exit(EXIT_FAILURE);
		}
		else // if it is the parent process
		{
			close(client_sd); // close the copy of client/secondary socket in parent process
		}
	}
	// close
	close(server_sd);
	return 0;
}
