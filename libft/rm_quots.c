/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quots.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:56:42 by mde-avel          #+#    #+#             */
/*   Updated: 2024/02/24 18:31:02 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//printf("len:%d\n", len);	
//len = (int)ft_strlen(new);
//printf("new: |%s| len: %d\n", new, len);	
/* char	*rm_quots(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 1;
	len = (int)ft_strlen(str) - 2;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	if (!str)
		return (NULL);
	while (j <= len) 
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(str);
	return (new);
} */

//printf("cmd: |%s| c: %c\n", aux, aux[len]);
//printf("new: |%s| c: %c \n", aux, aux[len]);
char	*if_quot_marks(char *cmd_line)
{
	char	*new;
	char	*aux;
	int		len;

	aux = ft_strdup(cmd_line);
	len = ft_strlen(aux) - 1;
	while (1)
	{
		if ((aux[0] == '"' && aux[len] == '"') || 
			(aux[0] == '\'' && aux[len] == '\''))
		{
			aux = rm_quots(aux);
			len = ft_strlen(aux) - 1;
		}
		else
			break ;
	}
	new = ft_strdup(aux);
	free(aux);
	return (new);
}
