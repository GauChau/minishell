/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:23:06 by jsaintho          #+#    #+#             */
/*   Updated: 2024/11/07 11:23:14 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	f__env(t_env *env2, int fdout)
{
	t_env	*env;

	env = env2;
	while (env && env->next != NULL)
	{
		if (ft_strchr(env->value, '='))
		{
			ft_putstr_fd(env->key, fdout);
			ft_putchar_fd('=', fdout);
			ft_putendl_fd(env->val, fdout);
		}
		env = env->next;
	}
	if (env && ft_strchr(env->value, '='))
		ft_putendl_fd(env->value, fdout);
	return (SUCCESS);
}
