/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:48:53 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/12 14:46:55 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_c_args(t_minishell	*t_m)
{
	int	i;

	i = 0;
	while (t_m->c_args[i])
	{
		free(t_m->c_args[i]);
		i++;
	}
	free(t_m->c_args[i]);
	free(t_m->c_args);
}

int	open_file(char *file, int in_out, int append)
{
	int	ret;

	if (in_out == 0)
		ret = open(file, O_RDONLY, 0644);
	if (in_out == 1 && !append)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (in_out == 1 && append)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (ret == -1)
	{
		if (errno == EISDIR)
		{
			ft_putstr_fd("Error: ", 2);
			ft_putstr_fd(file, 2);
			ft_putstr_fd(" is a directory\n", 2);
			return (-1);
		}
		perror("minishell");
		return (ret);
	}
	return (ret);
}

char	*get_env(char **env)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		s = ft_substr(env[i], 0, j);
		if (ft_strcmp(s, &("PATH"[0])) == 0)
		{
			free(s);
			return (env[i] + j + 1);
		}
		free(s);
		i++;
	}
	return (NULL);
}

char	*bget_path2(char *cmd, char **env)
{
	char	**b_path;
	char	**e_cmd;
	char	*exec_cmd;
	char	*str_path;
	int		i;

	i = -1;
	b_path = ft_split_quotes(get_env(env), ':', 0);
	e_cmd = ft_split_quotes(cmd, ' ', 1);
	while (b_path && b_path[++i])
	{
		str_path = ft_strjoin(b_path[i], "/");
		exec_cmd = ft_strjoin(str_path, e_cmd[0]);
		free(str_path);
		if (access(exec_cmd, F_OK | X_OK) == 0)
			return (exec_cmd);
		free(exec_cmd);
	}
	if (e_cmd)
		ft_free_tab(e_cmd);
	if (b_path)
		ft_free_tab(b_path);
	return (cmd);
}

int	exec_init(t_minishell *t_m)
{
	t_m->pid = ft_calloc(t_m->cmd_count + 1, sizeof(pid_t));
	if (!t_m->pid)
		return (perror("pid array creation error."), -1);
	t_m->pipes_fd = ft_calloc(t_m->cmd_count + 1, sizeof(int [2]));
	if (!t_m->pipes_fd)
		return (perror("pipes array creation error."), free(t_m->pid), -1);
	return (0);
}
