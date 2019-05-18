#ifndef CERBERUS_H
# define CERBERUS_H

# include <sys/types.h>
# include <sys/socket.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <string.h>

void				print_error(char *s);
char				*get_input(int client_fd);
struct addrinfo		*get_servinfo(char *hostname);
char				*get_ip_from_hostname(char *hostname);
int					is_http(char *arg);
int					build_host_fd(char *ip, int *server_fd_2);
int					send_response(char *buffer, int server_fd_2, int host_fd);

#endif
