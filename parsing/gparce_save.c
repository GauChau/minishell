/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gparce_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:37 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/11 18:29:28 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_inout(t_cmd *cmd)
{
	if (cmd->files->is_in)
		cmd->is_piped_in = 0;
	if (cmd->files->is_in)
		cmd->is_stdin = 0;
	if (cmd->files->is_out)
		cmd->is_piped_out = 0;
	if (cmd->files->is_out)
		cmd->is_stdout = 0;
}

int	ft_cmdlist_process(t_cmd *cmd, int cmd_count)
{
	int		i;
	t_files	*flist;

	i = 0;
	cmd[0].is_piped_in = 0;
	cmd[0].is_piped_out = 0;
	cmd[0].is_stdin = 1;
	cmd[0].is_stdout = 1;
	while (i < cmd_count)
	{
		ft_gchau_cparse(&cmd[i], cmd_count, i);
		flist = cmd[i].files;
		while (flist)
		{
			set_inout(&cmd[i]);
			flist = flist->next;
		}
		i++;
	}
	return (1);
}

int	gparse(char *line, t_minishell *t_m)
{
	char	**cmd_list;

	if (g_prserrors(line) == -1)
		return (-1);
	cmd_list = ft_split_quotes(line, '|', 0);
	t_m->cmd_count = ft_tablen(cmd_list);
	if (ft_cmd_creat(cmd_list, t_m) == -1)
		return (-1);
	ft_fill_cmd(cmd_list, t_m->commands);
	ft_cmdlist_process(t_m->commands, t_m->cmd_count);
	ft_free_tab(cmd_list);
	return (0);
}
