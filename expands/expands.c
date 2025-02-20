/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_machine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:38:49 by gchauvot          #+#    #+#             */
/*   Updated: 2024/11/29 18:05:12 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define BEGIN 0
#define KEY 1
#define TEMP 2

int	exp_quest(t_minishell *t_m, char *line[3], int *i)
{
	line[KEY] = ft_itoa(t_m->exstat % 255);
	line[TEMP] = ft_strjoin(line[BEGIN], line[KEY]);
	free(line[BEGIN]);
	free(line[KEY]);
	line[BEGIN] = line[TEMP];
	line[KEY] = NULL;
	line[TEMP] = NULL;
	(*i)++;
	return (1);
}

int	exp_finisher(t_env *env, char *line[3])
{
	if (findenv(line[KEY], env))
		line[TEMP] = ft_strjoin(line[BEGIN],
				(findenv(line[KEY], env))->val);
	else
		line[TEMP] = ft_strjoin(line[BEGIN], "");
	free(line[KEY]);
	return (0);
}

int	exp_finisher2(char *line[3], char *src, int i)
{
	if (src[i])
		line[KEY] = ft_strjoin(line[TEMP], &src[i]);
	else
		line[KEY] = ft_strdup(line[TEMP]);
	return (0);
}

char	*exp_tamp(t_minishell *t_m, t_env *env, char *src, int i)
{
	int		keystart;
	char	*line[3];

	line[TEMP] = NULL;
	if (src[i + 1] == '\0' || src[i + 1] == ' ')
		return (src);
	line[BEGIN] = ft_substr(src, 0, i);
	keystart = ++i;
	while (src[i])
	{
		if (!ft_isalnum(src[keystart]) && src[keystart] != '_'
			&& src[keystart] != '?')
			return (free(line[BEGIN]), src);
		if (src[i] == '?')
			if (exp_quest(t_m, line, &i))
				break ;
		if (!ft_isalnum(src[i]) && src[i] != '_')
			break ;
		i++;
	}
	line[KEY] = ft_substr(src, keystart, i - keystart);
	exp_finisher(env, line);
	exp_finisher2(line, src, i);
	return (free(line[BEGIN]), free(line[TEMP]), free(src), line[KEY]);
}

char	*apply_exp(t_minishell *t_m, char *line)
{
	int		i;
	int		memo;
	bool	sq;

	i = 0;
	sq = 0;
	memo = 0;
	while (line && line[i])
	{
		if (line[i] == '\'')
			sq = !sq;
		if (!sq)
		{
			if (line[i] == '$' && memo < 2)
			{
				line = exp_tamp(t_m, t_m->env, line, i);
				memo++;
				continue ;
			}
			memo = 0;
		}
		i++;
	}
	return (line);
}
/*
char    *exp_tamp(t_minishell *t_m, t_env *env, char *src, int i)
{
	int     keystart;
	// char    *begin;
	// char    *temp;
	// char    *key;
	char    *line[3];

	temp = NULL;
	if (src[i + 1] == ' ' || src[i + 1] == '\0')
		return (src);
	begin = ft_substr(src, 0, i);
	keystart = ++i;
	while (src[i])
	{
		if (ft_char_in_set(src[keystart], " \'\""))
			return (free(begin), src);
		if (src[i] == '?')
		{
			key = ft_itoa(t_m->exstat % 255);
			temp = ft_strjoin(begin, key);
			free(begin);
			free(key);
			begin = temp;
			key = NULL;
			temp = NULL;
			i++;
			break ;
		}
		if (ft_char_in_set(src[i], " \'\""))
			break ;
		i++;
	}
	key = ft_substr(src, keystart, i - keystart);
	if (findenv(key, env))
		temp = ft_strjoin(begin, (findenv(key, env))->val);
	else
		temp = ft_strdup(begin);
	free(key);
	if (src[i])
		key = ft_strjoin(temp, &src[i]);
	else
		key = ft_strdup(temp);
	return (free(begin), free(temp), free(src), key);
}
char *apply_exp(t_minishell *t_m, char *line)
{
	int     i;
	bool    sq;

	i = 0;
	sq = 0;
	if (!line)
		return (NULL);
	while(line[i])
	{
		if (line[i] == '\'')
			sq = !sq;
		if (!sq)
			if (line[i] == '$')
				line = exp_tamp(t_m, t_m->env, line, i);
		if (!line[i])
			break ;
		i++;
	}
	return (line);
}*/
