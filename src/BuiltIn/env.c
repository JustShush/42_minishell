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
	char	pwd[PATH_MAX + 1];

	tmp = *lst;
	if (!tmp)
	{
		perror("Minishell$> env");
		return ;
	}
	while (tmp)
	{
		if (ft_strncmp((char *)(tmp)->content, "PWD=", 4) == 0)
		{
			getcwd(pwd, sizeof(pwd));
			ft_printf("%s%d%s PWD=%s\n", YELLOW, (tmp)->n, RESET, pwd);
		}
		else
			ft_printf("%s%d%s %s\n", YELLOW, (tmp)->n, RESET, (tmp)->content);
		tmp = (tmp)->next;
	}
}

void	env(t_minishell *ms, char **cmd_line)
{
	if (cmd_line[1])
	{
		perror("Minishell$> env");
		ms->exit = 2;
		return ;
	}
	if (ms->env == NULL)
	{
		write(2, "No environment variables found.\n", 32);
		return ;
	}
	print_lst(ms->env);
}
