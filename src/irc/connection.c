#include <irc/connection.h>
#include <stdio.h>
#include <libft.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>

static char	msg_buffer[IRC_MESSAGE_MAXLEN + 1];

void	irc_receive(int fd)
{
	fd_set		fds;
	int			highest_fd;
	int			activity;
	ssize_t		msg_len;

	if (fd > 0)
	{
		FD_ZERO(&fds);
		FD_SET(STDIN_FILENO, &fds);
		FD_SET(fd, &fds);
		highest_fd = (fd > STDIN_FILENO) ? fd : STDIN_FILENO;
		activity = select(highest_fd + 1, &fds, NULL, NULL, NULL);
		if (activity >= 0 && FD_ISSET(fd, &fds))
		{
			msg_len = recv(fd, msg_buffer, sizeof(msg_buffer), 0);
			if (msg_len < 0)
				perror("recv");
			else if (msg_len == 0)
				printf("Disconnected!");
			else
				write(STDOUT_FILENO, msg_buffer, msg_len);
		}
	}
}

int	irc_send(int fd, const char* line)
{
	int			err;
	size_t		msg_len;

	msg_len = ft_strlcpy(msg_buffer, line, sizeof(msg_buffer));
	if (msg_len + sizeof(IRC_MESSAGE_SUFFIX) - 1 >= sizeof(msg_buffer))
	{
		ft_printf("send: Cannot send: Message too long");
		err = -1;
	}
	else
	{
		msg_len = ft_strlcat(msg_buffer, IRC_MESSAGE_SUFFIX, sizeof(msg_buffer));
		err = send(fd, msg_buffer, msg_len, 0);
	}
	return (err);
}

int	irc_connect(int fd, const char *hostname, const char* service)
{
	struct addrinfo	hints;
	struct addrinfo	*server_addr;
	int				err;

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_IP;

	ft_printf("Connecting to %s:%s...\n", hostname, service);

	err = getaddrinfo(hostname, service, &hints, &server_addr);

	if (err != 0)
	{
		ft_printf("%s: Host not found!\n", hostname);
		if (err == EAI_SYSTEM)
			perror("getaddrinfo");
	}
	else
	{
		err = connect(fd, server_addr->ai_addr, server_addr->ai_addrlen);
		if (err != 0)
			perror("connect");
	}

	freeaddrinfo(server_addr);

	return (err);
}
