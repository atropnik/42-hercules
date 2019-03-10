/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atropnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 02:09:40 by atropnik          #+#    #+#             */
/*   Updated: 2019/03/01 02:35:52 by atropnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	socket_create(void)
{
	int		sock;

	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		ft_puterror_fd("Creating socket failed.", STDOUT);
	ft_putendl_fd("Socket successfully created.", STDOUT);
	return (sock);
}

static void	socket_bind(int sock, int addr, int port)
{
	g_server.sin_family = PF_INET;
	g_server.sin_addr.s_addr = addr;
	g_server.sin_port = htons(port);
	if (bind(sock, (struct sockaddr *)&g_server, sizeof(g_server)) < 0)
		ft_puterror_fd("Binding unsuccessful", STDOUT);
	ft_putendl_fd("Binding successful.", STDOUT);
}

static int	accept_connection(int server_socket)
{
	int		len;
	int		client_socket;

	len = sizeof(struct sockaddr_in);
	if ((client_socket = accept(server_socket, (struct sockaddr *)&g_client, \
			(socklen_t*)&len)) < 0)
		ft_puterror_fd("Failed to accept! Try again.", STDOUT);
	ft_putendl_fd("Connection accepted.", STDOUT);
	return (client_socket);
}

static void	receive_message(int client_socket)
{
	int		read_size;
	char	client_message[BUFF_SIZE];

	while ((read_size = recv(client_socket, client_message, BUFF_SIZE, 0)) > 0)
	{
		if (!(ft_strncmp(client_message, "ping", 4)) \
				&& (client_message[5] == '\n' || client_message[5] == '\0'))
			ft_putendl_fd("pong pong", client_socket);
		ft_bzero(client_message, BUFF_SIZE);
	}
	if (!(read_size))
		ft_putendl_fd("Client disconnected. Stopping server.", STDOUT);
	else if (read_size == -1)
		ft_puterror_fd("Error receving  message from socket.", STDOUT);
}

int			main(int argc, char **argv)
{
	int		server_socket;
	int		client_socket;

	int		become_daemon;
	if (argc == 2 && (!(ft_strncmp(argv[1], "-D", 2))))
	{
		become_daemon = 1;
		daemonize(become_daemon);
	}
	server_socket = socket_create();
	socket_bind(server_socket, INADDR_ANY, PORT_NBR);
	listen(server_socket, BACKLOG);
	ft_putendl_fd("Waiting for connections...", STDOUT);
	client_socket = accept_connection(server_socket);
	receive_message(client_socket);
	return (0);
}
