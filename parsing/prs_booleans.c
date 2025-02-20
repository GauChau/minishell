/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prs_booleans.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:01:17 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/11 15:02:30 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setboules(t_gboules *boules)
{
	boules->dq = 0;
	boules->sq = 0;
	boules->inf = 0;
	boules->sup = 0;
	boules->other = 0;
	boules->space = 0;
	boules->pipe = 0;
	return (0);
}

void	qt_state_conds(t_gboules *boules, char c)
{
	if (c == '<')
		(boules->inf)++;
	else if (c == '>')
		(boules->sup)++;
	else if (c == ' ')
		(boules->space)++;
	if (c == '|')
		(boules->pipe)++;
	else if (!ft_char_in_set(c, " |"))
		boules->pipe = 0;
	if (ft_char_in_set(c, "<> |"))
	{
		(boules->other) = 0;
		if (c != ' ' && boules->inf < 2 && boules->sup < 2)
			boules->space = 0;
	}
	else
		(boules->other)++;
}

int	qt_state(t_gboules *boules, char c)
{
	if (c == '"' && !(boules->sq))
		boules->dq = !(boules->dq);
	else if (c == '\'' && !(boules->dq))
		boules->sq = !(boules->sq);
	if (!(boules->dq) && !(boules->sq))
		return (qt_state_conds(boules, c), 1);
	else
		return (0);
}

int	fl_determ(char *line, t_files *sfile)
{
	int	head;

	head = 0;
	if (line[head] == '>')
		sfile->is_out = 1;
	else if (line[head] == '<')
		sfile->is_in = 1;
	head++;
	if (line[head] == '<')
		sfile->is_heredoc = 1;
	if (line[head] == '>')
		sfile->is_append = 1;
	if (line[head] == '<' || line[head] == '>')
		head++;
	while (line[head] == ' ')
		head++;
	return (head);
}

int	ft_update_cmd(t_cmd *cmd, char *line, int head)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(line, 0, head);
	if (!tmp)
		return (-1);
	if (cmd->command == NULL && ft_strlen(tmp) > 0)
		cmd->command = ft_strdup(tmp);
	else
	{
		tmp2 = cmd->command;
		cmd->command = ft_strjoin(tmp2, tmp);
		free(tmp2);
	}
	free(tmp);
	return (0);
}
