/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:16:06 by dimarque            #+#    #+#             */
/*   Updated: 2023/11/17 13:16:06 by dimarque           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int		i;
	char	a;
	char	b;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	a = s1[i];
	b = s2[i];
	return (a - b);
}
