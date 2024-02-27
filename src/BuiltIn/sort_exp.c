/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:52:26 by dimarque          #+#    #+#             */
/*   Updated: 2024/02/27 22:32:14 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sort_env(t_minishell *ms, t_list **env)
{
	int		swapped;
	t_list	*ptr1;
	t_list	*lptr;

	swapped = 1;
	lptr = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *env;
		while (ptr1->next != lptr)
		{
			if (strcmp(ptr1->ident, ptr1->next->ident) > 0)
			{
				list_swap(ms, ptr1);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	print_env(t_list **env)
{
	t_list	*current;

	current = *env;
	while (current != NULL)
	{
		if (ft_strcmp(current->ident, "_") == 0)
		{
			if (current->next)
				current = current->next;
			else
				break ;
		}
		ft_printf("%s%s%s %s=\"%s\"\n", CYAN, "declare -x", RESET, \
					current->ident, current->content);
		current = current->next;
	}
}

t_list	*node(t_list *new_node, t_list *env)
{
	new_node = malloc(sizeof(t_list));
	new_node->ident = ft_strdup(env->ident);
	new_node->content = ft_strdup((char *)env->content);
	new_node->next = NULL;
	return (new_node);
}

t_list	*copy_env(t_list *env)
{
	t_list	*head;
	t_list	*tail;
	t_list	*new_node;

	head = NULL;
	tail = NULL;
	new_node = NULL;
	while (env)
	{
		new_node = node(new_node, env);
		if (tail == NULL)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		env = env->next;
	}
	return (head);
}

void	sort_and_print(t_minishell *ms)
{
	t_list	*tmp_env;
	t_list	*next;
	t_list	*current;

	if ((*ms->env) == NULL || (*ms->env)->ident == NULL)
		return ;
	tmp_env = copy_env(*ms->env);
	sort_env(ms, &tmp_env);
	print_env(&tmp_env);
	current = tmp_env;
	while (current != NULL)
	{
		next = current->next;
		free(current->ident);
		free(current->content);
		free(current);
		current = next;
	}
}
