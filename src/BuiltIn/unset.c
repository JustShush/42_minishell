/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:12:42 by dimarque          #+#    #+#             */
/*   Updated: 2024/01/24 12:12:42 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	rm_first_last(t_list **env)
{
	t_list	*last;
	t_list	*tmp;

	tmp = *env;
	while (tmp->next->next != NULL)
		tmp = tmp->next;
	last = tmp->next;
	tmp->next = NULL;
	free(last->content);
	free(last);
}

void	remove_node(t_list **env, char *ident, size_t len)
{
	t_list	*tmp;
	t_list	*lst;

	lst = *env;
	if (!lst)
		return ;
	while (lst->next != NULL)
	{
		if (ft_strncmp((char *)(lst)->next->content, ident, len) == 0)
		{
			if (lst->next->next == NULL)
			{
				rm_first_last(env);
				break ;
			}
			tmp = lst->next;
			lst->next = lst->next->next;
			free(tmp->content);
			free(tmp);
		}
		else if (ft_strncmp((char *)(lst)->content, ident, len) == 0)
		{
			tmp = (*env);
			*env = (*env)->next;
			lst = *env;
			free(tmp->content);
			free(tmp);
		}
		lst = lst->next;
	}
}

void	find_ident_unset(t_list **env, char *ident2)
{
	char	*ident1;
	size_t	len;
	char	*c;

	len = ft_strlen(ident2);
	remove_node(env, ident2, len);
	c = "=";
	ident1 = ft_strjoin(ident2, c);
	remove_node(env, ident1, len + 1);
	free(ident1);
}

/*export hi
unset hii*/
void	unset(t_minishell *ms, char **cmd_line)
{
	int	i;
	int flag;

	i = 1;
	if (!cmd_line[i])
		return ;
	while (cmd_line[i])
	{
		flag = ft_identifier(cmd_line[i]);
		if(flag == 0)
		{
			error_message(ms, "unset: not a valid identifier\n", cmd_line[i]);
			ms->exit = 1;
			break ;
		}
		if(flag == 2)
			break ;
		find_ident_unset(ms->env, cmd_line[i]);
		i++;
	}
}
//_=./minishell -> can't be remmoved