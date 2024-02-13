/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:48:28 by dimarque          #+#    #+#             */
/*   Updated: 2024/02/13 15:46:54 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*set_prompt(t_minishell *ms)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*dir;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		prompt = malloc(sizeof(char) * 12);
		if (!prompt)
			error(ms, 2, NULL, NULL);
		prompt = "Minishell$> ";
		return (prompt);
	}
	dir = ft_strjoin(ft_strrchr(getcwd(cwd, sizeof(cwd)), '/') + 1, "$> ");
	if (!dir)
		error(ms, 2, NULL, NULL);
	prompt = ft_strjoin("Minishell:", dir);
	if (!prompt)
		error(ms, 2, NULL, NULL);
	free(dir);
	return (prompt);
}
// maybe try to print the entire path until the user
// (~/documents/42_minishell) instead of 
// (/home/dimarque/documents/42_minishell)
