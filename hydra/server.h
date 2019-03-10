/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atropnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 02:09:40 by atropnik          #+#    #+#             */
/*   Updated: 2019/03/01 02:35:52 by atropnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <arpa/inet.h>

# define STDOUT		(1)
# define BUFF_SIZE	(4096)
# define PORT_NBR	(2121)
# define BACKLOG	(3)

struct sockaddr_in	g_server;
struct sockaddr_in	g_client;

void	ft_bzero(void *s, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_puterror_fd(const char *msg, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	daemonize(int become_daemon);
#endif
