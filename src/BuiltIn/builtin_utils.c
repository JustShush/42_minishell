/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-avel <mde-avel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:56:03 by mde-avel          #+#    #+#             */
/*   Updated: 2024/02/07 16:44:03 by mde-avel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*env_strchr(const char *str, int c)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = -1;
	j = -1;
	while (str[++i])
	{
		if (str[i] == (char)c)
			break ;
	}
	if (i == (int)ft_strlen(str))
		return (NULL);
	len = ft_strlen(str) - i + 1;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (str[i])
		res[++j] = str[++i];
	return (res);
}

t_list	*ft_envnew(void *content)
{
	t_list	*head;
	char	**new_cont;

	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	if (!ft_strchr(content, '='))
	{
		head->ident = ft_strjoin(content, "=");
		head->content = NULL;
	}
	else
	{
		new_cont = ft_split(content, '=');
		head->ident = ft_strjoin(new_cont[0], "=");
		head->content = env_strchr(content, '=');
		free_arr(new_cont);
	}
	head->next = NULL;
	return (head);
}
