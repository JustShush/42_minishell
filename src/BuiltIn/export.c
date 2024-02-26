/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:28 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/17 10:46:28 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//export _=poop A1=Desenhada A2=Banda
//export hi ho hiho
//export A1=Banana A2=Casca_de A3=Macaco_atira
//export hi=bye hi=hello A1=folha ho=

int	valid_ident(char *s)
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
			return (0);
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}

//ft_printf("%sident: %s|%s|\n", PURPLE, RESET, ident);
//ft_printf("%snew_cont: %s|%s|\n", YELLOW, RESET, new_cont);
//free((tmp)->ident);
//free((tmp)->content);
//return (free2(ident, new_cont), 0);
int	find_ident(t_list **env, char *ident, char *new_cont, int flag)
{
	t_list	*tmp;

	tmp = *env;
	if (!tmp)
		perror("Minishell$> export");
	while (tmp)
	{
		if (ft_strcmp((char *)(tmp)->ident, ident) == 0)
		{
			if (flag == 2 && (tmp)->n == 1)
				return (1);
			if (flag == 1 && (tmp)->n == 2)
			{
				(tmp)->n = 1;
				(tmp)->equal = 1;
			}
			free((tmp)->content);
			(tmp)->content = ft_strdup(new_cont);
			free(new_cont);
			free(ident);
			return (2);
		}
		tmp = (tmp)->next;
	}
	return (0);
}

//ft_printf("%scmd_line:%s|%s|\n", GREEN, RESET, content);
//ft_printf("%sidentifier:%s|%s|\n", YELLOW, RESET, ident);
//ft_printf("%snew_contet:%s|%s|\n", PURPLE, RESET, new_con);
int	check_identifier(t_minishell *ms, char *content)
{
	char	*ident;
	char	*new_con;
	int		flag;

	flag = 0;
	new_con = get_cont(content, '=');
	ident = get_ident(content, '=');
	if (valid_ident(ident) == 1)
		flag = get_flag(ms, ident, new_con, content);
	else if (valid_ident(ident) == 0)
	{
		error(ms, 1, "export: not a valid identifier\n", ident);
		ms->exit = 1;
	}
	if (flag == 1 || flag == 3 || flag == 0)
	{
		free(ident);
		free(new_con);
	}
	return (flag);
}

void	ft_export_2(t_minishell *ms, char *content, int check)
{
	t_list	*new;

	if (check == 1)
	{
		new = ft_envnew(content);
		new->n = 1;
		new->equal = 1;
		ft_lstadd_front(ms->env, new);
	}
	if (check == 3)
	{
		new = ft_envnew(content);
		new->n = 2;
		new->equal = 0;
		ft_lstadd_front(ms->env, new);
	}
}

void	sort_env(t_list **env)
{
    int swapped;
    t_list *ptr1;
    t_list *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = *env;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->ident, ptr1->next->ident) > 0) {
                char *temp_ident = ptr1->ident;
                ptr1->ident = ptr1->next->ident;
                ptr1->next->ident = temp_ident;

                void *temp_content = ptr1->content;
                ptr1->content = ptr1->next->content;
                ptr1->next->content = temp_content;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void print_env(t_list **env)
{
	t_list *current;

	current =  *env;
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

t_list *copy_env(t_list *env) {
    t_list *head = NULL;
    t_list *tail = NULL;
    
    // Iterate through original env list
    while (env != NULL) {
        // Create a new node
        t_list *new_node = malloc(sizeof(t_list));
        if (new_node == NULL) {
            // Error handling if memory allocation fails
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }

        // Copy ident and content
        new_node->ident = strdup(env->ident);
        new_node->content = strdup((char *)env->content);
        new_node->next = NULL;

        // Append new node to the new list
        if (tail == NULL) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }

        // Move to next node in original env list
        env = env->next;
    }
    
    return head;
}

void sort_and_print(t_minishell *ms) {
    if (ms == NULL || ms->env == NULL || *ms->env == NULL) {
        printf("No environment variables to sort or print.\n");
        return;
    }

    // Create a temporary copy of env
    t_list *tmp_env;
	tmp_env = copy_env(*ms->env);

    // Sort the temporary copy
    sort_env(&tmp_env);

    // Print the sorted environment variables
    printf("Sorted Environment Variables:\n");
    print_env(&tmp_env);

    // Free the memory allocated for the temporary copy
    t_list *current = tmp_env;
    while (current != NULL) {
        t_list *next = current->next;
        free(current->ident);
        free(current->content);
        free(current);
        current = next;
    }
}

void	ft_export(t_minishell *ms, char **cmd_line)
{
	int		i;
	int		check;
	char	*content;

	i = 1;
	//t_list *tmp_env = duplicate_env(*(ms->env));
	if (!cmd_line[i])
	{
		sort_and_print(ms);
		/* sort_env(tmp_env);
		print_sorted_env(tmp_env);
		free_env(tmp_env); */

		//print_lst(tmp, 2);
		return ;
	}
	while (cmd_line[i])
	{
		content = ft_strdup(cmd_line[i]);
		check = check_identifier(ms, content);
		ft_export_2(ms, content, check);
		i++;
		free(content);
	}
}
/*
printf("check: %d\n", flag);
export ho ho ho _=poop
export A1=Desenhada A2=Banda 
export A1=Banana A2=Casca_de A3=Macaco_atira
*/
