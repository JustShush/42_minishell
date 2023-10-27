/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:29:03 by dimarque          #+#    #+#             */
/*   Updated: 2022/11/04 17:55:29 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned long	i;
	const char		*a;
	char			*b;

	a = (const char *)src;
	b = (char *)dest;
	i = -1;
	if (!dest && !src)
		return (NULL);
	while (++i < n)
	{
		*(b + i) = *(a + i);
	}
	return (dest);
}

/* int	main(void)
{
	char *src;
	char *dest;
	char *ret;
	src = calloc(11, sizeof(char));
	src = "0123456789";
	dest = calloc(11, sizeof(char));
	ret = ft_memcpy(dest, src, 10);
	printf("src: %s\n", src);
	printf("dest: %s\n", dest);
	printf("ret: %s\n", ret);
	return (0);
} */