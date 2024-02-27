/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quots.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:56:42 by mde-avel          #+#    #+#             */
/*   Updated: 2024/02/24 20:51:08 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
