#include "cerberus.h"

int					is_http_1(char *arg)
{
	char	*tmp;
	int		len;
	int		i;

	tmp = strrchr(arg, ' ');
	if (tmp != NULL)
	{
		if (!strncmp(tmp + 1, "HTTP/1.0", 8))
			return (1);
		return (0);
	}
	return (0);
}

struct addrinfo		*get_servinfo(char *hostname)
{
	struct addrinfo		hints;
	struct addrinfo		*servinfo;
	struct addrinfo		*p;
	int					rv;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if ((rv = getaddrinfo((const char *)hostname, "http", \
		&hints, &servinfo)) != 0)
		print_error("Problem getting addrinfo");
	p = servinfo;
	freeaddrinfo(servinfo);
	return (p);
}

char				*get_ip_from_hostname(char *hostname)
{
	char				*ip;
	struct addrinfo		*p;
	struct sockaddr_in	*h;

	ip = (char *)malloc(sizeof(char) * 100);
	bzero(ip, 100);
	p = NULL;
	p = get_servinfo(hostname);
	while (p != NULL)
	{
		h = (struct sockaddr_in *)p->ai_addr;
		strcpy(ip, inet_ntoa(h->sin_addr));
		if (p)
			p = p->ai_next;
	}
	return (ip);
}

void				print_error(char *s)
{
	perror(s);
	exit(0);
}

char				*get_input(int client_fd)
{
	char	tmp[10000];
	char	*input;

	bzero(tmp, 10000);
	if (!(read(client_fd, tmp, 10000)))
		return (NULL);
	if (!(input = strdup(tmp)))
		return (NULL);
	return (input);
}
