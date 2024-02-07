/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-avel <mde-avel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:56:03 by mde-avel          #+#    #+#             */
/*   Updated: 2024/02/07 15:32:16 by mde-avel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*env_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
		{
			str++;
			return ((char *)str);
		}
		str++;
	}
	if ((char)c == '\0')
	{
		return ((char *)str);
	}
	return (0);
}

t_list	*ft_envnew(void *content)
{
	t_list	*head;
	char	**new_cont;

	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	if (env_strchr(content, '=') == 0)
	{
		head->ident = ft_strjoin(content, "=");
		head->content = NULL;
	}
	else
	{
		new_cont = ft_split(content, '=');
		head->ident = ft_strjoin(new_cont[0], "=");
		head->content = env_strchr(content, '=');
		//free_arr(new_cont);
	}
	head->next = NULL;
	return (head);
}
