/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spliter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:09:49 by jsaintho          #+#    #+#             */
/*   Updated: 2024/12/11 16:47:00 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char src, bool *dq, bool *sq)
{
	if (src == '"' && !(*sq))
		*dq = !(*dq);
	else if (src == '\'' && !(*dq))
		*sq = !(*sq);
	return (0);
}

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;
	bool	dq;
	bool	sq;
	bool	wbol;

	words = 0;
	i = 0;
	sq = 0;
	dq = 0;
	wbol = 0;
	while (s[i])
	{
		if (!sq && !dq && s[i] != c && !wbol)
		{
			wbol = !wbol;
			words++;
		}
		if (!sq && !dq && s[i] == c)
			wbol = 0;
		check_quotes(s[i], &dq, &sq);
		i++;
	}
	return (words);
}

int	setres(char *src, int *i, t_gboules *balls, char c)
{
	int	count;

	count = 0;
	while (src[*i + count])
	{
		if (src[*i + count] == c && !(balls->sq) && !(balls->dq))
			break ;
		check_quotes(src[*i + count], &(balls->dq), &(balls->sq));
		count++;
	}
	return (count);
}

int	filler(char *src, int words, char **splitted, char c)
{
	int			i;
	int			j;
	int			count;
	t_gboules	balls;

	i = 0;
	j = 0;
	ft_setboules(&balls);
	while (src[i] && j < words)
	{
		if (!balls.dq && !balls.sq)
			count = setres(src, &i, &balls, c);
		if (count)
			splitted[j++] = ft_substr(src, i, count);
		if (count)
			i += count;
		else
			i += 1;
	}
	splitted[j] = 0;
	return (0);
}

char	**ft_split_quotes(char *s, char c, int remove_quote)
{
	size_t	words;
	char	**tab;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	tab = ft_calloc((words + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	filler(s, words, tab, c);
	if (remove_quote)
		apply_quote_removal(tab);
	return (tab);
}
