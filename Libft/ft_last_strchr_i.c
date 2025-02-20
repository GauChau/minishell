/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:27:51 by jsaintho          #+#    #+#             */
/*   Updated: 2024/07/15 17:30:08 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_last_strchr_i(const char *string, char a, char b)
{
	char	*str;
	int		i;
	int		ix;

	i = 0;
	ix = -1;
	str = (char *)string;
	while (*str != 0)
	{
		if (*str == a || *str == b)
			ix = i;
		str++;
		i++;
	}
	return (ix);
}
