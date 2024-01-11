/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:33 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 10:46:33 by marvin           ###   ########.fr       */
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
		perror("Minishell$> unset");
	while (lst->next != NULL)
	{
		if (ft_strncmp((char *)(lst)->next->content, ident, len) == 0)
		{
			if (lst->next->next == NULL)
			{
				rm_first_last(env);
				break;
			}
			tmp = lst->next;	
			lst->next = lst->next->next;
			free(tmp->content);
			free(tmp);
		}
		else if(ft_strncmp((char *)(lst)->content, ident, len) == 0)
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

void	unset(t_minishell *ms, char **cmd_line)
{
	int	i;

	i = 1;
	if (!cmd_line[i])
		return ;
	while (cmd_line[i])
	{
		if(ft_identifier(cmd_line[i]) == 0)
		{
			printf("Minishell$> unset: '%s': not a valid identifier\n", cmd_line[i]);
			ms->exit = 2;
			break ;
		}
		find_ident_unset(ms->env, cmd_line[i]);
		i++;
	}
}
