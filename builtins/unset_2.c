/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:01:15 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/11 17:07:01 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_check(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[0]))
		return (0);
	while (arg[i] != 0)
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

t_env	*findenv_next(char *name, t_env *env)
{
	t_env	*h;

	h = env;
	if (!name)
		return (NULL);
	if (name[0] == 0)
		return (NULL);
	while (h->next)
	{
		if (!ft_strncmp(name, h->next->value, ft_strlen(name)))
			return (h);
		if (!ft_strcmp(name, h->next->key))
			return (h);
		h = h->next;
	}
	return (NULL);
}
