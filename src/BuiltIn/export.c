/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:28 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 10:46:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//export Ho Ho 		-> declare -x Ho
//export Ho=poop 	-> env & no declare -x
int	find_ident_exp(t_list **env, char *ident, char *new_cont, int flag)
{
	t_list	*tmp;
	size_t	len;

	tmp = *env;
	if (!tmp)
		perror("Minishell$> export");
	if (flag == 1)
		ident = ft_strjoin(ident, "=");
	else
		ident = ft_strdup(new_cont);
	len = ft_strlen(ident);
	while (tmp)
	{
		if ((tmp)->n == flag && \
			ft_strncmp((char *)(tmp)->content, ident, len) == 0)
		{
			free((tmp)->content);
			(tmp)->content = new_cont;
			free(ident);
			return (2);
		}
		tmp = (tmp)->next;
	}
	free(ident);
	return (0);
}

int	check_ident2(t_minishell *ms, char *content, char **ident)
{
	int	flag;

	flag = 0;
	if (!ft_strchr(content, '='))
	{
		if (find_ident_exp(ms->env, NULL, content, 2) == 2)
			flag = 4;
		else
			flag = 3;
	}
	else
	{
		if (ident[1])
		{
			if (find_ident_exp(ms->env, ident[0], content, 1) == 2)
				flag = 2;
			else
				flag = 1;
		}
	}
	free_arr(ident);
	return (flag);
}

int	check_identifier(t_minishell *ms, char *content)
{
	char	**ident;
	int		flag;

	flag = 0;
	ident = ft_split(content, '=');
	if (ft_identifier(ident[0]) == 1)
	{
		flag = check_ident2(ms, content, ident);
	}
	else if (ft_identifier(ident[0]) == 0)
	{
		error_message(ms, "export: not a valid identifier\n", content);
		ms->exit = 1;
	}
	free_arr(ident);
	return (flag);
}

void	ft_export2(int check, char	*content, t_minishell *ms)
{
	t_list	*new;

	if (check == 1)
	{
		new = ft_lstnew(content);
		new->n = 1;
		ft_lstadd_front(ms->env, new);
	}
	if (check == 3)
	{
		new = ft_lstnew(content);
		new->n = 2;
		ft_lstadd_front(ms->env, new);
	}
}

void	ft_export(t_minishell *ms, char **cmd_line)
{
	int		i;
	int		check;
	char	*content;

	i = 1;
	if (!cmd_line[i])
	{
		print_lst(ms->env, 2);
		return ;
	}
	while (cmd_line[i])
	{
		content = ft_strdup(cmd_line[i]);
		check = check_identifier(ms, content);
		if (check == 0)
			break ;
		ft_export2(check, content, ms);
		i++;
	}
}

/*
printf("check: %d\n", flag);
export ho ho ho _=poop
export A1=Desenhada A2=Banda 
export A1=Banana A2=Casca_de A3=Macaco_atira
*/