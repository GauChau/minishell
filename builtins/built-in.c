/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:15:52 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/12 12:46:52 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	restorefds(t_cmd *c, int fd_stds[2])
{
	if (!c->is_stdin)
	{
		dup2(fd_stds[0], 0);
		close(fd_stds[0]);
	}
	if (!c->is_stdout)
	{
		dup2(fd_stds[1], 1);
		close(fd_stds[1]);
	}
	return (0);
}

int	openfds(t_minishell *t_m, t_cmd *c, int fd_stds[2], int fd_duped[2])
{
	t_files	*flist;

	flist = c->files;
	fd_stds[1] = 0;
	fd_stds[0] = 0;
	while (flist)
	{
		if (fd_stds[flist->is_out])
			restorefds(c, fd_stds);
		fd_stds[flist->is_out] = dup(flist->is_out);
		flist->filename = apply_exp(t_m, rm_quotes(flist->filename));
		fd_duped[flist->is_out] = open_file(flist->filename,
				flist->is_out, flist->is_append);
		if (fd_duped[flist->is_out] == -1)
		{
			t_m->exstat = 1;
			return (-1);
		}
		dup2(fd_duped[flist->is_out], flist->is_out);
		close(fd_duped[flist->is_out]);
		flist = flist->next;
	}
	return (0);
}

int	builtindirector(t_minishell *t_m, t_cmd *c, int n_builtin)
{
	int	fd_stds[2];
	int	fd_duped[2];

	t_m->exp_starter = n_builtin;
	if (openfds(t_m, c, fd_stds, fd_duped) == -1)
		return (restorefds(c, fd_stds), -1);
	run_builtin(t_m, n_builtin, 1, c);
	restorefds(c, fd_stds);
	return (0);
}

int	is_builtin(char *c)
{
	if (!c)
		return (-1);
	if (ft_strcmp(c, "echo") == 0)
		return (1);
	if (ft_strcmp(c, "cd") == 0)
		return (2);
	if (ft_strcmp(c, "pwd") == 0)
		return (3);
	if (ft_strcmp(c, "env") == 0)
		return (4);
	if (ft_strcmp(c, "export") == 0)
		return (5);
	if (ft_strcmp(c, "unset") == 0)
		return (6);
	if (ft_strcmp(c, "exit") == 0)
		return (7);
	return (-1);
}

void	run_builtin(t_minishell *t_m, int n_builtin, int fdout, t_cmd *cmd)
{
	t_m->exstat = 0;
	if (n_builtin == 1)
		f__echo(t_m->c_args, fdout);
	if (n_builtin == 2)
		f__cd(t_m->c_args, t_m);
	if (n_builtin == 3)
		if (f__pwd(fdout))
			t_m->exstat = 1;
	if (n_builtin == 4)
		f__env(t_m->env, fdout);
	if (n_builtin == 5)
		f__export(t_m);
	if (n_builtin == 6)
		if (f__unset(t_m))
			t_m->exstat = 1;
	if (n_builtin == 7)
		f__exit(t_m, cmd);
}
