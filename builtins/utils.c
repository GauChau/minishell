/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:13:30 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/11 17:14:38 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	filltab(t_env **tab, t_env *env)
{
	int		i;
	t_env	*filler;

	i = 0;
	filler = env;
	while (filler)
	{
		tab[i++] = filler;
		filler = filler->next;
	}
}

void	sort_env_tab(t_env **tab, int len)
{
	int		i;
	t_env	*temp;

	i = 0;
	while (i < len)
	{
		if (ft_strcmp(tab[i + 1]->value, tab[i]->value) < 0)
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
			continue ;
		}
		i++;
	}
}
