#include "cerberus.h"

int		build_host_fd(char *ip, int *server_fd_2)
{
	struct sockaddr_in	host_addr;
	int					host_fd;
	char				buffer[1000];
	int					port;
	struct hostent		*host;

	if (!(host = gethostbyname(ip)))
		print_error("Error getting host address. Exiting");
	bzero(buffer, 1000);
	port = 80;
	bzero((char*)&host_addr, sizeof(host_addr))	;
	host_addr.sin_port = htons(port);
	host_addr.sin_family = AF_INET;
	bcopy((char *)host->h_addr, \
		(char*)&host_addr.sin_addr.s_addr, host->h_length);
	*server_fd_2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	host_fd = connect(*server_fd_2, \
		(struct sockaddr*)&host_addr, sizeof(struct sockaddr));
	sprintf(buffer, "\nConnected to %s  IP - %s\n", \
		ip, inet_ntoa(host_addr.sin_addr));
	printf("%s\n", buffer);
	if (host_fd < 0)
		print_error("Error connecting to remote server");
	return (host_fd);
}

int		send_response(char *buffer, int server_fd_2, int host_fd)
{
	int n;

	n = send(server_fd_2, buffer, strlen(buffer), 0);
	if (n < 0)
		print_error("Sorry, error writing to socket");
	else
	{
		while (n > 0)
		{
			bzero((char*)buffer, 1000);
			n = recv(server_fd_2, buffer, 1000, 0);
			if (!(n <= 0))
			{
				puts(buffer);
				send(host_fd, buffer, n, 0);
			}
		}
	}
	return (1);
}
