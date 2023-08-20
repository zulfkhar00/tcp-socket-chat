#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// constants
#define SERVER_IP "127.0.0.1"
#define PORT 6000
#define MAX_MSG_LEN 1024

int main(int argc, char *argv[])
{
	int client_socket;
	struct sockaddr_in server_address;
	char buffer[MAX_MSG_LEN];
	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) // if socket isn't created
	{
		printf("Failed to create socket\n");
		exit(EXIT_FAILURE);
	}
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	if (inet_pton(AF_INET, SERVER_IP, &server_address.sin_addr) <= 0)
	{
		printf("Invalid server IP address\n");
		exit(EXIT_FAILURE);
	}
	if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) // if couldn't connect to server
	{
		printf("Failed to connect to server\n");
		exit(EXIT_FAILURE);
	}
	printf("Connected to server\n");
	while (1)
	{
		printf("Enter message: ");
		fgets(buffer, MAX_MSG_LEN, stdin); // read input message
		int msg_len = strlen(buffer);
		if (msg_len > 0 && buffer[msg_len - 1] == '\n') // to make the input be in one line, without
		{
			buffer[--msg_len] = '\0';
		}
		if (send(client_socket, buffer, msg_len, 0) < 0) // if couldn't send to the server
		{
			printf("Failed to send message\n");
			exit(EXIT_FAILURE);
		}
		if (strcmp(buffer, "BYE!") == 0) // termination condition
		{
			break;
		}
		int bytes_received = recv(client_socket, buffer, MAX_MSG_LEN, 0); // reply from server
		if (bytes_received < 0)
		{
			printf("Failed to receive message\n");
			exit(EXIT_FAILURE);
		}
		else if (bytes_received == 0) // server is closed
		{
			printf("Connection closed by server\n");
			break;
		}
		else
		{
			buffer[bytes_received] = '\0';
			printf("Server response: %s\n", buffer);
		}
	}
	close(client_socket);
	return 0;
}