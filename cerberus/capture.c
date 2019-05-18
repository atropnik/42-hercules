#include "cerberus.h"

int						contacting_host(int client_fd, char *hostname, char *path)
{
	char				buffer[1000];
	int					host_fd;
	char				*ip;
	int					n;
	int					server_fd_2;

	ip = get_ip_from_hostname(hostname);
	server_fd_2 = -1;
	host_fd = build_host_fd(ip, &server_fd_2);
	bzero(buffer, 1000);
	sprintf(buffer, "GET %s %s\r\nHost: %s\r\nConnection: close\r\n\r\n", \
		path, "HTTP/1.0", ip);
	free(ip);
	printf("SENDING: %s\n", buffer);
	send_response(buffer, server_fd_2, host_fd);
	return (1);
}

int						parse_url(char *tmp, char **hostname, char **path)
{
	char	*tmp2;
	int		len;
	char	tmp_path[1000];

	len = 0;
	bzero(tmp_path, 1000);
	tmp2 = strtok(tmp, "/");
	if (!tmp2 || strncmp(tmp2, "http:", 5))
		print_error("Please prefix URL with 'http'");
	tmp2 = strtok(NULL, "/");
	*hostname = strdup(tmp2);
	strcpy(tmp_path, "/");
	while (tmp2 != NULL)
	{
		tmp2 = strtok(NULL, "/");
		if (tmp2)
		{
			strcat(tmp_path, tmp2);
			if (!strchr(tmp_path, '.'))
				strcat(tmp_path, "/");
		}
	}
	*path = strdup(tmp_path);
	return (1);
}

int						parse_input(int client_fd)
{
	char					*input;
	char					*tmp;
	char					request[1000];
	char					*hostname;
	char					*path;

	tmp = NULL;
	bzero(request, 1000);
	hostname = NULL;
	path = NULL;
	if ((input = get_input(client_fd)))
	{
		if (!is_http(input))
			print_error("Specify HTTP/1.0. Connecting failed.\n");
		tmp = strtok(input, " ");
		strcpy(request, tmp);
		tmp = strtok(NULL, " ");
		if (!parse_url(tmp, &hostname, &path))
			print_error("Problem with URL. Connecting failed.\n");
		contacting_host(client_fd, hostname, path);
	}
	else
		print_error("Failed to get input. Now Exiting.\n");
	return (1);
}

struct sockaddr_in		get_server_socket_fd(int port)
{
	struct sockaddr_in		s_addr;

	bzero((char*)&s_addr, sizeof(s_addr));
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(port);
	s_addr.sin_addr.s_addr = INADDR_ANY;
	return (s_addr);
}

int						main(int ac, char **av)
{
	struct sockaddr_in	s_addr;
	struct sockaddr_in	c_addr;
	int					server_socket;
	int					client_fd;

	if (ac != 2 || atoi(av[1]) < 0 || atoi(av[1]) > 65535)
		print_error("Enter valid port numbers only.\n");
	bzero((char*)&c_addr, sizeof(c_addr));
	s_addr = get_server_socket_fd(atoi(av[1]));
	if ((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) \
		&& server_socket < 0)
		print_error("Error - socket not initialized.\n");
	if (bind(server_socket, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0)
		print_error("Failed to assign local end's port number");
	listen(server_socket, 10);
	if ((client_fd = accept(server_socket, (struct sockaddr *)NULL, NULL)) \
		&& client_fd < 0)
		print_error("Error connecting.\n");
	parse_input(client_fd);
	close(client_fd);
	close(server_socket);
	return (0);
}
