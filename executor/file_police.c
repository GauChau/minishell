/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_police.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 16:41:20 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/12 14:53:33 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	closepipesonfail(t_minishell *t_m, t_cmd *c, int i)
{
	close(t_m->pipes_fd[i][0]);
	close(t_m->pipes_fd[i][1]);
	if (i > 0)
	{
		if (!c->is_piped_in)
			close(t_m->pipes_fd[i - 1][0]);
		if (!c->is_piped_in)
			close(t_m->pipes_fd[i - 1][1]);
	}
	exit(1);
}

int	child_molestor(t_minishell *t_m, t_cmd *c, size_t i, int c_int)
{
	signalsetter(SIGINT, SIG_DFL);
	signalsetter(SIGQUIT, SIG_DFL);
	if (childhead_handler(t_m, i, c) == -1)
		closepipesonfail(t_m, c, i);
	if (i > 0)
	{
		if (!c->is_piped_in)
			close(t_m->pipes_fd[i - 1][0]);
		if (!c->is_piped_in)
			close(t_m->pipes_fd[i - 1][1]);
	}
	if (c_int != -1)
		run_builtin(t_m, c_int, 1, c);
	else if (c->command)
		ft_exec2(c->command, t_m->nenv);
	exit(0);
}

int	childhead_handler(t_minishell *t_m, size_t i, t_cmd *c)
{
	int		fd;
	t_files	*flist;

	flist = c->files;
	while (flist)
	{
		fd = open_file(rm_quotes(apply_exp(t_m, flist->filename)),
				flist->is_out, flist->is_append);
		if (fd == -1)
			return (-1);
		dupclose(fd, flist->is_out);
		flist = flist->next;
	}
	if (i > 0 && c->is_piped_in)
	{
		dupclose(t_m->pipes_fd[i - 1][0], 0);
		close(t_m->pipes_fd[i - 1][1]);
	}
	close(t_m->pipes_fd[i][0]);
	if (c->is_piped_out)
		dupclose(t_m->pipes_fd[i][1], 1);
	else
		close(t_m->pipes_fd[i][1]);
	return (0);
}

int	hall_monitor(t_minishell *t_m, size_t i)
{
	if (i > 0)
	{
		close(t_m->pipes_fd[i - 1][0]);
		close(t_m->pipes_fd[i - 1][1]);
	}
	if (i == t_m->cmd_count - 1)
	{
		close(t_m->pipes_fd[i][0]);
		close(t_m->pipes_fd[i][1]);
	}
	return (0);
}
