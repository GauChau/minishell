/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchauvot <gchauvot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:03:25 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/12 15:06:38 by gchauvot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*findenv(char *name, t_env *env)
{
	t_env	*h;

	h = env;
	if (!name)
		return (NULL);
	if (name[0] == 0)
		return (NULL);
	while (h)
	{
		if (!ft_strncmp(name, h->value, ft_strlen(name)))
			return (h);
		if (!ft_strcmp(name, h->key))
			return (h);
		h = h->next;
	}
	return (NULL);
}

int	env_len(t_env *t)
{
	int		i;
	t_env	*h;

	i = 0;
	h = t;
	while (h->next)
	{
		i++;
		h = h->next;
	}
	return (i + 1);
}

void	display(int argc, t_env **argv)
{
	int	i;

	i = -1;
	while (++i < argc)
	{
		if ((argv[i]->key)[0] == '_')
			continue ;
		printf("export %s", argv[i]->key);
		if ((argv[i]->val))
			printf("=\"%s\"\n", (argv[i]->val));
		else
			printf("\n");
	}
}

int	env_lastadd(t_env *t, char *value)
{
	int		i;
	t_env	*h;
	t_env	*new;
	char	*dump;

	i = 0;
	h = t;
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (-1);
	while (h->next)
		h = h->next;
	h->next = new;
	new->value = ft_strdup(value);
	if (ft_strchr(value, '='))
		new->val = ft_strdup(ft_strchr(value, '=') + 1);
	dump = ft_substr(value, 0, ft_strlen(value)
			- (size_t)(ft_strlen(new->val) + 1));
	if (!ft_strchr(value, '='))
		new->key = ft_strdup(value);
	else
		new->key = ft_strdup(dump);
	free(dump);
	new->next = NULL;
	return (i);
}

t_env	*env_add_void(char *value)
{
	t_env	*new;
	char	*dump;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = ft_strdup(value);
	if (ft_strchr(value, '='))
		new->val = ft_strdup(ft_strchr(value, '=') + 1);
	dump = ft_substr(value, 0, ft_strlen(value)
			- (size_t)(ft_strlen(new->val) + 1));
	new->key = ft_strdup(dump);
	free(dump);
	new->next = NULL;
	return (new);
}
