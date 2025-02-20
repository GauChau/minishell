/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilcs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:57:42 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/12 16:22:01 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

int	error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	ft_putstr_fd("minishell: ", STDERR);
	ft_putstr_fd(rm_quotes(path), STDERR);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
	{
		ret = 127;
		ft_putendl_fd(": command not found", 2);
	}
	else
		ret = 126;
	if (folder)
		closedir(folder);
	ft_close(fd);
	if (ret == 127)
		if (access(path, R_OK) == -1 && !access(path, F_OK))
			ret = 126;
	return (ret);
}

int	isspc_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ft_waiter(t_minishell *t_m)
{
	size_t	i;
	int		catcher;

	i = 0;
	while (i < (t_m->cmd_count))
	{
		waitpid(t_m->pid[i], &catcher, 0);
		if (WIFSIGNALED(catcher))
		{
			t_m->exstat = 128 + WTERMSIG(catcher);
			write(2, "\n", 1);
		}
		else
			t_m->exstat = catcher;
		i++;
	}
	return (0);
}
