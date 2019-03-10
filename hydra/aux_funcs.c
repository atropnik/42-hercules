/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atropnik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 02:09:40 by atropnik          #+#    #+#             */
/*   Updated: 2019/03/01 02:35:52 by atropnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	ft_putendl_fd(const char *s, int fd)
{
	int		i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
	write(fd, "\n", 1);
}

void	ft_puterror_fd(const char *msg, int fd)
{
	ft_putendl_fd(msg, fd);
	exit(1);
}

void	ft_bzero(void *s, size_t n)
{
	size_t		i;

	i = 0;
	while (n--)
		((unsigned char *)s)[i++] = 0;
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ns1;
	unsigned char	*ns2;

	if (!n)
		return (0);
	ns1 = (unsigned char *)s1;
	ns2 = (unsigned char *)s2;
	while ((*ns1 && (*ns1 == *ns2)) && --n)
	{
		if (*ns1 != *ns2)
			return (*ns1 - *ns2);
		ns1 += 1;
		ns2 += 1;
	}
	return (*ns1 - *ns2);
}

void	daemonize(int become_daemon) 
{
	if (become_daemon) 
	{
		int daemon_pid = fork();
		if (daemon_pid == 0)
			return ;
		else if (daemon_pid == -1) 
			ft_putendl_fd("Forking process failed. Cannot start as daemon.\n", STDOUT);
		else
			exit(0);
		return;
	}
}
