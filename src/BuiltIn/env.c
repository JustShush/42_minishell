/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:23 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/17 10:46:23 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	list_swap(t_minishell *ms, t_list *list)
{
	char	*ident;
	void	*content;
	t_list	*head;
	t_list	*tmp;

	ident = NULL;
	content = NULL;
	head = list;
	if (!head && !head->next)
	{
		write(2, "List Swap Error\n", 16);
		ms->exit = 1;
		return ;
	}
	tmp = head;
	ident = tmp->ident;
	content = tmp->content;
	head->ident = head->next->ident;
	head->content = head->next->content;
	head->next->ident = ident;
	head->next->content = content;
}

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
			ft_printf("%s%s=%s%s\n", GREEN, (tmp)->ident, RESET, (tmp)->content);
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

void	env(t_minishell *ms)
{
	if (ms->env == NULL)
	{
		error(ms, 1, "env: No environment variables found.\n", NULL);
		return ;
	}
	print_lst(ms->env, 1);
}
