/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quots.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-avel <mde-avel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:56:42 by mde-avel          #+#    #+#             */
/*   Updated: 2024/02/22 19:58:14 by mde-avel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*rm_quots(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 1;
	len = (int)ft_strlen(str) - 2;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	while (j <= len) 
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
