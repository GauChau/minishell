/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_machine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:49 by gchauvot          #+#    #+#             */
/*   Updated: 2024/11/29 18:05:12 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;
	t_env	*dump;

	tmp = env;
	while (tmp)
	{
		if (tmp->key)
			free(tmp->key);
		tmp->key = NULL;
		if (tmp->val)
			free(tmp->val);
		if (tmp->value)
			free(tmp->value);
		tmp->val = NULL;
		dump = tmp;
		tmp = tmp->next;
		free(dump);
	}
}

void	free_shit(t_minishell *t_m)
{
	free(t_m->pid);
	free(t_m->pipes_fd);
}

void	free_flist(t_files	*flist)
{
	t_files	*tmp;

	while (flist)
	{
		if (flist->filename)
			free(flist->filename);
		tmp = flist->next;
		free(flist);
		flist = tmp;
	}
}

void	free_mesenp(t_minishell *t_m)
{
	t_cmd	*cmd;
	size_t	i;

	i = 0;
	if (t_m->commands)
	{
		cmd = t_m->commands;
		while (i < t_m->cmd_count)
		{
			if (cmd[i].files)
				free_flist((cmd[i].files));
			if (cmd[i].command)
				free(cmd[i].command);
			i++;
		}
		if (cmd)
			free(cmd);
	}
	t_m->commands = NULL;
}
