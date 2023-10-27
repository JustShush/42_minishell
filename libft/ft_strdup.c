/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:16:24 by dimarque          #+#    #+#             */
/*   Updated: 2022/11/10 16:52:50 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		strlen;
	char	*str1;

	strlen = ft_strlen(str);
	str1 = (char *)malloc(sizeof(char) * strlen + 1);
	if (!str1)
		return (NULL);
	return (ft_memcpy(str1, str, strlen + 1));
}

/* int main() {

	printf("%s",ft_strdup("leite"));

	return 0;
}
 */