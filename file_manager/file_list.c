/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:03:48 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/11 18:29:18 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files	*creat_tfile(t_cmd *cmd)
{
	t_files	*tmp;

	tmp = ft_calloc(1, sizeof(struct s_files));
	if (!tmp)
		return (NULL);
	tmp->filename = NULL;
	tmp->is_append = 0;
	tmp->is_heredoc = 0;
	tmp->is_in = 0;
	tmp->is_out = 0;
	tmp->is_piped_in = 0;
	tmp->is_piped_out = 0;
	tmp->is_stdin = 0;
	tmp->is_stdout = 0;
	tmp->next = NULL;
	if (ft_addtfile(cmd, tmp) == -1)
		return (free(tmp), NULL);
	return (tmp);
}

void	ft_updt_stdp(t_files *sfiles, t_cmd *cmd)
{
	if (sfiles->is_in)
	{
		cmd->is_piped_in = 0;
		cmd->is_stdin = 0;
		if (sfiles->is_heredoc)
			cmd->is_heredoc = 1;
	}
	if (sfiles->is_out)
	{
		cmd->is_piped_out = 0;
		cmd->is_stdout = 0;
	}
}

int	ft_file_add(char *line, t_cmd *cmd)
{
	t_files		*sfile;
	int			head;
	int			start;
	t_gboules	boulas;

	ft_setboules(&boulas);
	sfile = creat_tfile(cmd);
	if (!sfile)
		return (ft_putendl_fd("sfilecreat error", 2), -1);
	head = fl_determ(line, sfile);
	ft_updt_stdp(sfile, cmd);
	start = head;
	while (line[head])
	{
		if (qt_state(&boulas, line[head]))
			if (ft_char_in_set(line[head], " ><"))
				break ;
		head++;
	}
	sfile->filename = ft_substr(line, start, head - start);
	return (head);
}

int	ft_prs_files(char *line, t_cmd *cmd)
{
	int			head;
	int			start;
	t_gboules	boulas;

	head = 0;
	start = 0;
	ft_setboules(&boulas);
	while (line[head])
	{
		if (qt_state(&boulas, line[head]))
		{
			if (line[head] == '<' || line[head] == '>')
			{
				ft_update_cmd(cmd, &line[start], head - start);
				head += ft_file_add(&line[head], cmd);
				start = head;
				continue ;
			}
		}
		head++;
	}
	if (start != head)
		ft_update_cmd(cmd, &line[start], head);
	return (0);
}

int	ft_gchau_cparse(t_cmd *cmd, int cmd_count, int i)
{
	char	*line;

	line = cmd->prompt;
	if (i == 0 && cmd_count > 1)
	{
		cmd->is_piped_out = 1;
		cmd->is_stdout = 0;
	}
	else if (cmd_count > 1 && i == cmd_count - 1)
	{
		cmd->is_piped_in = 1;
		cmd->is_stdout = 1;
	}
	else if (i && i != cmd_count -1)
	{
		cmd->is_piped_in = 1;
		cmd->is_piped_out = 1;
	}
	if (ft_prs_files(line, cmd) == -1)
		return (-1);
	return (0);
}
