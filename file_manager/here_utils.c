/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:18:17 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/11 16:19:39 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredocalloc(t_minishell *t_m)
{
	t_cmd	*c;
	size_t	i;
	t_files	*lfiles;

	i = 0;
	while (i <= t_m->cmd_count - 1)
	{
		c = &(t_m->commands[i]);
		lfiles = c->files;
		if (c->is_heredoc)
		{
			while (lfiles)
			{
				if (lfiles->is_heredoc)
					if (heredoc(t_m, lfiles) == -1)
						return (-1);
				lfiles = lfiles->next;
			}
		}
		i++;
	}
	return (1);
}

int	delete_heredocs(t_minishell *t_m)
{
	size_t	i;
	t_cmd	*c;
	t_files	*flist;

	i = 0;
	while (i < t_m->cmd_count)
	{
		c = &(t_m->commands[i]);
		flist = c->files;
		while (flist)
		{
			if (flist->is_heredoc)
			{
				if (access(flist->filename, F_OK) == 0)
				{
					if (unlink(flist->filename) == -1)
						perror("unlink heredoc: ");
				}
			}
			flist = flist->next;
		}
		i++;
	}
	return (0);
}
