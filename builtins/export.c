/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:26:34 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/12 15:02:35 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_customs(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]))
		return (-1);
	while (arg[i])
	{
		if (ft_char_in_set(arg[i], "=-_/\\"))
			return (-1);
		i++;
	}
	return (0);
}

int	s_and_chang_helper(char *arg, t_env *target)
{
	free(target->value);
	free(target->val);
	free(target->key);
	target->value = ft_strdup(arg);
	if (ft_strchr(arg, '='))
	{
		target->val = ft_strdup(ft_strchr(arg, '=') + 1);
		target->key = ft_strdup(ft_substr(arg, 0,
					ft_strlen(arg) - (size_t)(ft_strlen(target->val) + 1)));
	}
	else
	{
		target->val = ft_strdup(arg);
		target->key = arg;
	}
	return (0);
}

int	s_and_chang(char *arg, t_env *env, t_minishell *t_m)
{
	char	*tmp;
	t_env	*target;

	tmp = ft_substr(arg, 0,
			ft_strlen(arg) - (size_t)(ft_strlen(ft_strchr(arg, '='))));
	if (!ft_strlen(tmp) || export_customs(tmp) == -1)
		return (free(tmp),
			ft_putendl_fd("minishell: not a valid identifier", 2), -1);
	target = findenv(tmp, env);
	free(tmp);
	if (target)
		s_and_chang_helper(arg, target);
	else if (env)
		env_lastadd(env, arg);
	else
		t_m->env = env_add_void(arg);
	return (0);
}

void	fexport_helper(t_minishell *t, t_env *h)
{
	int		l;
	t_env	**w;

	l = env_len(t->env);
	w = ft_calloc(l + 1, sizeof(t_env *));
	if (!w)
		return ;
	if (t->c_args[1] == 0)
	{
		filltab(w, h);
		sort_env_tab(w, l - 1);
		display(l, w);
	}
	free(w);
}

void	f__export(t_minishell *t)
{
	t_env	*h;
	int		i;

	i = 1;
	h = t->env;
	t->exstat = 0;
	while (t->c_args[i] != 0)
	{
		t->c_args[i] = apply_exp(t, t->c_args[i]);
		if (s_and_chang(rm_quotes(t->c_args[i]), h, t) == -1)
			t->exstat = 1;
		i++;
	}
	h = t->env;
	i = 0;
	if (t->env)
		fexport_helper(t, h);
}
