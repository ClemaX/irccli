/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chamada <chamada@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:20:36 by chamada           #+#    #+#             */
/*   Updated: 2020/12/11 18:25:54 by chamada          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <term/term.h>
#include <signal.h>

#include <irc/connection.h>

void	do_nothing(int signal)
{
	(void)signal;
}


void	term_sig_interrupt(int signal)
{
	(void)signal;
	write(STDERR_FILENO, TERM_ENDL, sizeof(TERM_ENDL) - 1);
	if (g_term.msg)
		write(STDERR_FILENO, g_term.msg->data, g_term.msg->len);
	if (g_term.line && g_term.line->len)
	{
		g_term.line->len = 0;
		if (g_term.line->data)
			*g_term.line->data = '\0';
	}
}

/*
**	Read and parse a terminal's input.
*/

int		term_read(int connection_fd)
{
	int	read_st;

	irc_receive(connection_fd);
	free(g_term.line->data);
	g_term.line->data = NULL;
	g_term.line->len = 0;
	g_term.line->size = 0;
	signal(SIGINT, &term_sig_interrupt);
	if ((read_st = get_next_line(STDIN_FILENO, &g_term.line->data)) == -1)
		return (TERM_EREAD);
	signal(SIGINT, &do_nothing);
	g_term.line->len = ft_strlen(g_term.line->data);
	g_term.line->size = g_term.line->len + 1;
	if (read_st == 1 || (read_st == 0 && g_term.line->len != 0))
		return (TERM_ENL);
	return (TERM_EEOF);
}
