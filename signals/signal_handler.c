/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:43:14 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/11 18:18:08 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signalsetter(int signum, void (*handler)(int))
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = handler;
	sigaction(signum, &act, 0);
}

void	signalignore(int signum)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sigaction(signum, &act, 0);
}

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		g_sigcatch = 1;
		write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_sigcatch = 128 + signum;
		rl_done = 1;
		close(0);
	}
	return ;
}
