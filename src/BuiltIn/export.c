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
//export hi hi hi
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
			|| (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
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

int	find_ident_exp(t_list **env, char *ident, char *new_cont)
{
	t_list	*tmp;
	size_t	len;
	char	*c;

	tmp = *env;
	if (!tmp)
		perror("Minishell$> export");
	c = "=";
	ident = ft_strjoin(ident, c);
	len = ft_strlen(ident);
	while (tmp)
	{
		if (ft_strncmp((char *)(tmp)->content, ident, len) == 0)
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

int	check_identifier(t_minishell *ms, char *content)
{
	char	**ident;

	ident = ft_split(content, '=');
	if (!ident[1])
	{
		free_arr(ident);
		return (3);
	}
	if (ft_identifier(ident[0]) == 1)
	{
		if(find_ident_exp(ms->env, ident[0], content) == 2)
		{
			free_arr(ident);
			return (2);
		}
		free_arr(ident);
		return (1);
	}
	else if (ft_identifier(ident[0]) == 2)
		return (0);
	error_message(ms, "export: not a valid identifier\n", content);
	ms->exit = 1;
	free_arr(ident);
	return (0);
}

void	print_exp(t_list **lst)
{
	t_list	*tmp;
	char	*exp;

	tmp = *lst;
	exp = "declare -x";
	if (!tmp)
		return ;
	while (tmp)
	{
		ft_printf("%s%s%s %s\n", YELLOW, exp, RESET, (tmp)->content);
		tmp = (tmp)->next;
	}
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
		print_exp(ms->env);
		return ;
	}
	while (cmd_line[i])
	{
		content = ft_strdup(cmd_line[i]);
		check = check_identifier(ms, content);
		if (check == 0)
			break ;
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
		i++;
	}
}

//export A1=Desenhada A2=Banda 
//export A1=Banana A2=Casca_de A3=Macaco_atira