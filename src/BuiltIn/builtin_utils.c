/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-avel <mde-avel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:56:03 by mde-avel          #+#    #+#             */
/*   Updated: 2024/02/08 19:37:06 by mde-avel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//what is munmap_chunk(): invalid pointer?

char	*get_cont(const char *str, int c)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = -1;
	j = -1;
	while (str[++i])
		if (str[i] == (char)c)
			break ;
	if (str[i + 1] == '\0' || i == (int)ft_strlen(str))
		return (ft_strdup("  "));
	len = ft_strlen(str) - i + 1;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (str[i])
		res[++j] = str[++i];
	res[j] = '\0';
	return (res);
}

char	*get_ident(const char *str, int c, int flag)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	i = -1;
	j = 0;
	
	while (str[++i])
		if (str[i] == (char)c)
			break ;
	len = i + 1;
	res = malloc(sizeof(char) * len);
	if (!res)
		return (NULL);
	while (j <= i)
	{
		res[j] = str[j];
		j++;
	}
	if (flag == 0)
	{
		ft_printf("%sHEY!%s\n", YELLOW, RESET);
		res[j] = '=';
		j++;
	}
	res[j] = '\0';
	return (res);
}

t_list	*ft_envnew(void *content)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	if (ft_strchr(content, '=') == 0)
	{
		head->ident = get_ident(content, '=', 0);
		//ft_printf("%sident: %s%s\n", YELLOW, head->ident, RESET);
		head->content = "  ";
		//ft_printf("%scontent: %s%s\n", PURPLE, head->content, RESET);
	}
	else
	{
		//ft_printf("%sHi%s\n", YELLOW, RESET);
		head->ident = get_ident(content, '=', 1);
		head->content = get_cont(content, '=');
	}
	head->next = NULL;
	return (head);
}
