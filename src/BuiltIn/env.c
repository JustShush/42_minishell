/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:23 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 10:46:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_lst(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		if ((tmp)->n == 1)
			ft_printf("%s%d%s %s\n", YELLOW, (tmp)->n, RESET, (tmp)->content);
		tmp = (tmp)->next;
	}
}

void	env(t_minishell *ms, char **cmd_line)
{
	if (cmd_line[1])
	{
		error_message(ms, "env: Too many arguments\n", NULL);
		ms->exit = 127;
		return ;
	}
	if (ms->env == NULL)
	{
		error_message(ms, "env: No environment variables found.\n", NULL);
		return ;
	}
	print_lst(ms->env);
}
