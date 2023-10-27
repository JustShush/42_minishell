/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:39:14 by dimarque          #+#    #+#             */
/*   Updated: 2023/08/09 10:43:34 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	while (src[j] != '\0')
		j++;
	if (size != 0)
	{
		while ((src[i] != '\0') && (i < size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (j);
}

/* int	main(int argc, char **argv)
{
	long long unsigned int	a;
	int						b;

	if (argc != 4)
		return (0);
	a = atoi(argv[3]);
	b = ft_strlcpy(argv[1], argv[2], a);
	printf("src: %s\ndest: %s\nsrc_size: %d\n", argv[2], argv[1], b);
	return (0);
} */