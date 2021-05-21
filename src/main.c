#include <term/term.h>

t_term	g_term;

int	main(int ac, const char **av, const char **envp)
{
	(void)ac;
	(void)av;
	t_env		*env;
	t_term_err	err;
	const char	*line;

	if (!(env = env_import(envp)))
		return (errno);
	if ((err = term_init(&env, "WOWOWO", true)) != TERM_EOK)
	{
		term_perror(err);
		return (err);
	}
	while ((err = term_prompt(&line)) == TERM_ENL)
	{
		ft_printf("input: %s\n", line);
	}
	term_destroy();
	env_clr(&env);
	return (err);
}
