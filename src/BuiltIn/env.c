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

void	print_lst(t_list **lst, int flag)
{
	t_list	*tmp;
	char	*exp;

	tmp = *lst;
	if (!tmp)
		return ;
	if (flag == 2)
		exp = "declare -x";
	while (tmp)
	{
		if ((tmp)->n == 1 && flag == 1)
			ft_printf("%s%d%s %s%s\n", GREEN, (tmp)->n, RESET, (tmp)->ident, (tmp)->content);
		else if (flag == 2)
		{
			if (ft_strcmp((tmp)->content, "  ") == 0 && ft_strchr((tmp)->ident, '='))
				ft_printf("%s%s%s %s\"\"\n", CYAN, exp, RESET, (tmp)->ident);
			else if (!ft_strchr((tmp)->ident, '='))
				ft_printf("%s%s%s %s\n", CYAN, exp, RESET, (tmp)->ident);
			else
				ft_printf("%s%s%s %s\"%s\"\n", CYAN, exp, RESET, (tmp)->ident, (tmp)->content);
		}
			
		tmp = (tmp)->next;
	}
}

void	env(t_minishell *ms, char **cmd_line)
{
	if (cmd_line[1])
	{
		error(ms, 3, "env: Too many arguments\n");
		ms->exit = 127;
		return ;
	}
	if (ms->env == NULL)
	{
		error(ms, 3, "env: No environment variables found.\n");
		return ;
	}
	print_lst(ms->env, 1);
}
