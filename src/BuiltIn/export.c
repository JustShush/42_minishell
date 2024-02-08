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

int	ft_identifier(char	*s)
{
	int	i;
	int	flag;

	if (ft_strcmp(s, "_") == 0)
		return (2);
	if ((s[0] >= '0' && s[0] <= '9') || s[0] == '=')
		return (0);
	i = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9')
			|| (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_' || s[i] == '=')
			flag = 1;
		else
		{
			flag = 0;
			break ;
		}
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}

int	find_ident_exp(t_list **env, char *ident, char *new_cont, int flag)
{
	t_list	*tmp;
	size_t	len;

	(void)flag;
	tmp = *env;
	if (!tmp)
		perror("Minishell$> export");
	ft_printf("%sident: %s|%s|\n", PURPLE, RESET, ident);
	ft_printf("%snew_cont: %s|%s|\n", YELLOW, RESET, new_cont);
	len = ft_strlen(ident);
	while (tmp)
	{
		if (ft_strncmp((char *)(tmp)->ident, ident, len - 1) == 0)
		{
			(tmp)->ident = ident;
			ft_printf("%stmp->content: %s|%s|\n", BLUE, RESET, (tmp)->content);
			//free((tmp)->content);
			(tmp)->content = new_cont;
			ft_printf("%stmp->new_con: %s|%s|\n", YELLOW, RESET, (tmp)->content);
			return (2);
		}
		tmp = (tmp)->next;
	}
	return (0);
}
//export hi=bye hi=hello a1=folha ho

int	check_identifier(t_minishell *ms, char *content)
{
	char	*ident;
	char	*new_con;
	int		flag;

	flag = 0;
	ft_printf("%scmd_line:%s|%s|\n", GREEN, RESET, content);
	ident = get_ident(content, '=');
	new_con = get_cont(content, '=');
	//ft_printf("%sidentifier:%s|%s|\n", YELLOW, RESET, ident);
	//ft_printf("%snew_contet:%s|%s|\n", PURPLE, RESET, new_con);
	if (ft_identifier(ident) == 1)
	{
		if (!ft_strchr(content, '='))
		{
			if (find_ident_exp(ms->env, ident, new_con, 2) == 2)
				flag = 4;
			else
				flag = 3;
		}
		else
		{
			if (find_ident_exp(ms->env, ident, new_con, 1) == 2)
				flag = 2;
			else
				flag = 1;
		}
	}
	else if (ft_identifier(ident) == 0)
	{
		error(ms, 3, "export: not a valid identifier\n");
		ms->exit = 1;
	}
	printf("check flag: %d\n", flag);
	return (flag);
}

void	ft_export(t_minishell *ms, char **cmd_line)
{
	int		i;
	int		check;
	char	*content;
	t_list	*new;

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
		//ft_printf("%s%s%s\n", YELLOW, content,  RESET);
		if (check == 0)
			break ;
		if (check == 1)
		{
			new = ft_envnew(content);
			new->n = 1;
			ft_lstadd_front(ms->env, new);
		}
		if (check == 3)
		{
			new = ft_envnew(content);
			//ft_printf("%shello%s\n", PURPLE, RESET);
			new->n = 2;
			ft_lstadd_front(ms->env, new);
			//ft_printf("%sporra%s\n", YELLOW,  RESET);
		}
		i++;
	}
}
//export ho ho ho
//export _=poop
//export A1=Desenhada A2=Banda 
//export A1=Banana A2=Casca_de A3=Macaco_atira