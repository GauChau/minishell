/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:49:14 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/11 16:53:52 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dupclose(int fd2, int fd1)
{
	if (dup2(fd2, fd1) == -1)
		return (perror("minishell: dup2: "), exit(126), 1);
	if (close(fd2) == -1)
		return (perror("minishell: close: "), exit(126), 1);
	return (0);
}

void	ft_free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

char	**pipe_env(t_minishell *t_m)
{
	int		i;
	int		x;
	char	**env;
	t_env	*temp;

	i = 0;
	x = 0;
	temp = t_m->env;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	env = ft_calloc(i + 1, sizeof(char *));
	if (!env)
		return (NULL);
	temp = t_m->env;
	while (x < i)
	{
		env[x] = temp->value;
		temp = temp->next;
		x++;
	}
	return (env);
}

int	shl_help(int i, char **env)
{
	size_t	j;
	char	*res;

	j = 0;
	res = ft_itoa(ft_atoi(&env[i][6]) + 1);
	while (j < ft_strlen(res))
	{
		env[i][6 + j] = res[j];
		j++;
	}
	free(res);
	env[i][6 + j] = '\0';
	return (0);
}

void	shlvlhandler(char **env)
{
	int		i;
	int		mark;

	i = 0;
	mark = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			shl_help(i, env);
			mark = -1;
		}
		i++;
	}
	if (mark != -1)
	{
		env[i] = "SHLVL=0";
		env[i + 1] = 0;
	}
}
