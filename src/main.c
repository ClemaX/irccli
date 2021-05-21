#include <term/term.h>
#include <irc/connection.h>

#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

t_term	g_term;

static int	print_usage(const char *name)
{
	ft_printf("Usage: %s hostname service\n", name);
	return (-2);
}

static int	init(int ac, const char **av)
{
	int	socket_fd;

	if (ac != 3)
		return (print_usage(av[0]));
	socket_fd = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
	if (socket_fd < 0)
	{
		perror("socket");
		return (-1);
	}
	if (irc_connect(socket_fd, av[1], av[2]) != 0)
	{
		if (close(socket_fd) != 0)
			perror("close");
		return (-3);
	}
	ft_printf("Connected!\n");
	return (socket_fd);
}

static int	routine(int socket_fd)
{
	int			err;
	const char	*line;

	while ((err = term_prompt(&line, socket_fd)) == TERM_ENL)
		irc_send(socket_fd, line);
	return (err);
}

int	main(int ac, const char **av, const char **envp)
{
	t_env		*env;
	t_term_err	err;
	int			socket_fd;

	socket_fd = init(ac, av);
	if (socket_fd < 0)
		return (socket_fd);
	env = env_import(envp);
	if (!env)
	{
		perror("env_import");
		return (TERM_EALLOC);
	}
	if ((err = term_init(&env, "WOWOWO", true)) != TERM_EOK)
	{
		term_perror(err);
		return (err);
	}
	err = routine(socket_fd);
	term_destroy();
	env_clr(&env);
	if (close(socket_fd) != 0)
		perror("close");
	return (err);
}
