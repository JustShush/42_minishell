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

	if (s[0] >= '0' && s[0] <= '9')
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

int	find_ident(t_list **env, char *ident, char *new_cont)
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
	//printf("%sidentifier:%s %s\n", YELLOW, RESET, ident[0]);
	if (ft_identifier(ident[0]) == 1)
	{
		if(find_ident(ms->env, ident[0], content) == 2)
		{
			free_arr(ident);
			return (2);
		}
		free_arr(ident);
		return (1);
	}
	free_arr(ident);
	printf("Minishell$> export: '%s': not a valid identifier\n", ident[0]);
	return (0);
}

void	ft_export(t_minishell *ms, char **cmd_line)
{
	int		i;
	int		check;
	char	*content;
	t_list	*new;

	i = 1;
	while (cmd_line[i])
	{
		content = ft_strdup(cmd_line[i]);
		check = check_identifier(ms, content);
		if (check == 0)
			break ;
		if (check == 1)
		{
			new = ft_lstnew(content);
			new->n = i;
			ft_lstadd_front(ms->env, new);
		}
		i++;
	}
}

//export A1=Desenhada A2=Banda 
//export A1=Banana A2=Casca_de A3=Macaco_atira