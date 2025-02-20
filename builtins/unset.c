/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:21:49 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/12 13:07:36 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_t_var(char *s, char *d)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	j = ft_strlen(d);
	if (j > i)
		return (j);
	return (i);
}

void	free_node(t_minishell *t_m, t_env *env)
{
	if (t_m->env == env && env->next == NULL)
	{
		ft_memdel(t_m->env->value);
		t_m->env->value = NULL;
		t_m->env->next = NULL;
		return ;
	}
	ft_memdel(t_m->env->value);
	ft_memdel(t_m->env);
}

void	free_env_node(t_env *del)
{
	free(del->key);
	free(del->val);
	free(del->value);
	free(del);
	del = NULL;
}

int	new_unset(t_minishell *t_m, char *args)
{
	t_env	*del;
	t_env	*tmp;

	del = t_m->env;
	if (del)
	{
		if (!ft_strncmp(args, del->value, ft_strlen(args))
			|| !ft_strcmp(args, del->key))
		{
			t_m->env = del->next;
			free_env_node(del);
		}
	}
	if (!del->next)
		return (0);
	del = findenv_next(args, t_m->env);
	if (del)
	{
		tmp = del->next;
			del->next = del->next->next;
		free_env_node(tmp);
	}
	return (0);
}

int	f__unset(t_minishell *t_m)
{
	t_env	*h;
	char	**args;
	int		i;

	args = t_m->c_args;
	h = t_m->env;
	if (!h)
		return (1);
	i = 1;
	while (args[i])
	{
		if (!arg_check(args[i]))
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(args[i++], 2);
			ft_putstr_fd(": invalid parameter name\n", 2);
			continue ;
		}
		new_unset(t_m, args[i]);
		h = t_m->env;
		i++;
	}
	t_m->exstat = 0;
	return (SUCCESS);
}
