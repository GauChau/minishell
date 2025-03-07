/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:59:38 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/11 12:51:53 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	nb_args(char **args)
{
	int		size;

	size = 0;
	while (args[size])
		size++;
	return (size);
}

void	printechotab(char **args, int fdout)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], fdout);
		if (args[++i])
			write(fdout, " ", 1);
	}
}

int	f__echo(char **args, int fdout)
{
	int		i;
	int		j;
	int		n_option;

	i = 1;
	j = 0;
	n_option = 0;
	if (nb_args(args) > 1)
	{
		while (args[i] && args[i][0] == '-')
		{
			while (ft_char_in_set(args[i][++j], "n"))
				;
			if (args[i][j] != '\0')
				break ;
			i++;
			j = 0;
			n_option = 1;
		}
		printechotab(&args[i], fdout);
	}
	if (n_option == 0)
		write(fdout, "\n", 1);
	return (SUCCESS);
}
