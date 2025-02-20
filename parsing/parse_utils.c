/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:01:14 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/11 15:01:50 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_fill_cmd(char **tab, t_cmd *c)
{
	int	i;

	i = 0;
	while (i < ft_tablen(tab))
	{
		c[i].prompt = tab[i];
		i++;
	}
	return (0);
}

int	ft_cmd_creat(char **tab, t_minishell *t_m)
{
	int		i;
	t_cmd	*c;

	i = 0;
	c = NULL;
	t_m->commands = c;
	c = ft_calloc(ft_tablen(tab), sizeof(struct s_cmd));
	if (!c)
		return (-1);
	t_m->commands = c;
	c->files = NULL;
	c->is_piped_in = 1;
	c->is_piped_out = 1;
	c->is_stdin = 0;
	c->is_stdout = 0;
	return (i);
}

int	ft_addtfile(t_cmd *src, t_files *add)
{
	t_files	*temp;

	if (!src)
		return (-1);
	temp = src->files;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = add;
	}
	else
		src->files = add;
	return (0);
}
