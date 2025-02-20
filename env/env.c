/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:45:02 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/12 14:51:02 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_t_var(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

char	*get_env_path(t_minishell *t_m)
{
	t_env	*n;
	char	**spl;
	char	*v;
	int		j;

	n = (t_m->env);
	v = NULL;
	while (n)
	{
		if (ft_strncmp(n->value, "PATH", size_t_var(n->value)) == 0)
		{
			spl = ft_split(n->value, '=');
			v = spl[1];
			j = 0;
			while (spl[j])
			{
				free(spl[j]);
				j++;
			}
			break ;
		}
		n = n->next;
	}
	return (v);
}

t_env	*create_env_node(char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	if (value)
	{
		env->value = ft_strdup(value);
		if (ft_strlen(ft_strchr(value, '=')) > 0)
		{
			env->val = ft_strdup(ft_strchr(value, '=') + 1);
			env->key = ft_substr(value, 0,
					ft_strlen(value) - (size_t)ft_strlen(env->val) - 1);
		}
		else
			env->key = ft_strdup(value);
	}
	env->next = NULL;
	return (env);
}

int	env_init(t_minishell *t_m, char **envp, char *progname)
{
	t_env	*env;
	t_env	*new;
	int		i;

	t_m->env = NULL;
	if (envp == NULL)
		return (-1);
	t_m->env = create_env_node(envp[0]);
	env = t_m->env;
	i = 0;
	while (envp && envp[++i])
	{
		new = create_env_node(envp[i]);
		env->next = new;
		env = new;
	}
	if (!findenv("_", t_m->env))
	{
		new = create_env_node(progname);
		env->next = new;
		env = new;
	}
	env = t_m->env;
	return (0);
}
