/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gprs_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:27:14 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/09 18:18:10 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	errconds(t_gboules *bolas, char c)
{
	if (bolas->inf && bolas->sup)
		return (-1);
	if (bolas->pipe && (bolas->inf || bolas->sup))
		return (-1);
	if (bolas->inf > 2 || bolas->sup > 2 || bolas->pipe > 1)
		return (-1);
	if ((bolas->inf > 1 || bolas->sup > 1) && bolas->space
		&& ft_char_in_set(c, "><|"))
		return (-1);
	if (bolas->other && (bolas->inf || bolas->sup || bolas->pipe))
		ft_setboules(bolas);
	return (0);
}

int	g_prserrors(char *line)
{
	int			i;
	int			qtstate;
	t_gboules	bolas;

	ft_setboules(&bolas);
	i = 0;
	while (line[i] != 0)
	{
		qtstate = qt_state(&bolas, line[i]);
		if (qtstate)
			if (errconds(&bolas, line[i]) == -1)
				return (ft_putstr_fd("minishell: syntax error near ", 2),
					ft_putchar_fd(line[i], 2), write(2, "\n", 1), -1);
		i++;
	}
	if (!qtstate)
		return (ft_putendl_fd("minishell: syntax error near ' or \"", 2), -1);
	if (bolas.inf)
		return (ft_putendl_fd("minishell: syntax error near <", 2), -1);
	if (bolas.sup)
		return (ft_putendl_fd("minishell: syntax error near >", 2), -1);
	if (bolas.pipe || line[0] == '|')
		return (ft_putendl_fd("minishell: syntax error near |", 2), -1);
	return (0);
}
