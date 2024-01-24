/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:09:26 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 11:09:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	arr_size(char **arr)
{
	int	i;
	int	count;

	if (!arr)
		return (0);
	i = 0;
	count = 0;
	while (arr[i])
	{
		if (arr[i][0])
			count++;
		i++;
	}
	return (count);
}

char	**list_to_array(t_minishell *ms, t_list **list)
{
	int		i;
	int		size;
	t_list	*tmp;
	char	**buf;

	i = 0;
	tmp = *list;
	size = ft_lstsize(tmp);
	buf = malloc(sizeof(char *) * (size + 1));
	if (!buf)
		error(ms, 2, NULL);
	while (tmp && i < size)
	{
		buf[i] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	buf[i] = 0;
	return (buf);
}

void	print_arr(char *str, char **arr)
{
	int	i;
	int	j;

	i = 0;
	if (!arr)
		return ;
	j = arr_size(arr);
	printf("	%s:\n", str);
	while (arr[i] && i < j)
		printf("			%s\n", arr[i++]);
}