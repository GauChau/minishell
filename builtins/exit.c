/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:30:09 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/11 17:17:38 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_dig(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_char_in_set(str[i], "+-"))
			return (1);
		i++;
	}
	return (0);
}

void	f__exit(t_minishell *t_m, t_cmd *c)
{
	char	**tmp;
	int		i;

	i = 1;
	tmp = ft_split_quotes(c->command, ' ', 1);
	while (tmp[i])
	{
		if (i > 1)
		{
			t_m->exstat = 1;
			return (ft_putendl_fd("too many arguments", 2));
		}
		else if (is_str_dig(tmp[i]))
		{
			t_m->exstat = 2;
			ft_putendl_fd("numeric argument required", 2);
			break ;
		}
		else
			t_m->exstat = ft_atoi(tmp[i]);
		i++;
	}
	return (ft_free_tab(tmp), free_c_args(t_m), delete_heredocs(t_m),
		free_shit(t_m), ft_putendl_fd("exit", 1), exit(t_m->exstat));
}
