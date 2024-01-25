/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:33:27 by dimarque          #+#    #+#             */
/*   Updated: 2022/11/21 15:22:47 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nstr(char const *str, char c, char **list)
{
	int	i;
	int	len;

	i = 0;
	while (*str)
	{
		len = 0;
		while (*str == c && *str)
			str++;
		if (*str)
			i++;
		while (str[len] != c && str[len])
			len++;
		if (list && i && len)
			list[i - 1] = ft_substr(str, 0, len);
		while (*str != c && *str)
			str++;
	}
	return (i);
}

char	**ft_split(char const *str, char c)
{
	char	**token;

	token = ft_calloc(sizeof(char *), (ft_nstr(str, c, NULL) + 1));
	if (!token)
		return (NULL);
	ft_nstr(str, c, token);
	return (token);
}
