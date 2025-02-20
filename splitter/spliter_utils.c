/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spliter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:09:49 by jsaintho          #+#    #+#             */
/*   Updated: 2024/11/29 15:49:15 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_quotes(char *s)
{
	size_t	i;
	bool	dq;
	bool	sq;
	int		j;

	i = 0;
	j = 0;
	sq = 0;
	dq = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '"' && !sq)
			dq = !dq;
		else if (s[i] == '\'' && !dq)
			sq = !sq;
		else
			s[j++] = s[i];
		i++;
	}
	s[j] = '\0';
	return (s);
}

void	apply_quote_removal(char **t)
{
	size_t	i;

	i = 0;
	while (t[i])
	{
		t[i] = rm_quotes(t[i]);
		i++;
	}
	return ;
}
