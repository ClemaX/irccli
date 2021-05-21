#ifndef IRC_H
# define IRC_H

#define IRC_MESSAGE_SUFFIX "\r\n"
#define IRC_MESSAGE_MAXLEN 512U

void	irc_receive(int connection_fd);

int		irc_connect(int connection_fd, const char *hostname,
	const char* service);

int		irc_send(int connection_fd, const char* line);

#endif
