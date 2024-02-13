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

	exp = "declare -x";
	tmp = *lst;
	if (!tmp)
		return ;
	if (flag == 2)
		exp = "declare -x";
	while (tmp)
	{
		if ((tmp)->n == 1 && flag == 1)
			ft_printf("%s%s %s=%s\n", GREEN, (tmp)->ident, RESET, (tmp)->content);
		else if (flag == 2)
		{
			if ((tmp)->equal == 0 && ft_strcmp((tmp)->content, "  ") == 0)
				ft_printf("%s%s%s %s\n", CYAN, exp, RESET, (tmp)->ident);
			else if (ft_strcmp((tmp)->content, "  ") == 0)
				ft_printf("%s%s%s %s=\"\"\n", CYAN, exp, RESET, (tmp)->ident);
			else
				ft_printf("%s%s%s %s=\"%s\"\n", CYAN, exp, RESET, \
					(tmp)->ident, (tmp)->content);
		}
		tmp = (tmp)->next;
	}
}

void	env(t_minishell *ms, char **cmd_line)
{
	if (cmd_line[1])
	{
		error(ms, 1, "env: Too many arguments\n", NULL);
		ms->exit = 127;
		return ;
	}
	if (ms->env == NULL)
	{
		error(ms, 1, "env: No environment variables found.\n", NULL);
		return ;
	}
	print_lst(ms->env, 1);
}
