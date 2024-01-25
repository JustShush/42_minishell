/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:58:21 by dimarque          #+#    #+#             */
/*   Updated: 2024/01/25 15:47:00 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error(t_minishell *ms, int op, char *arg)
{
	if (op == 2)
	{
		printf("%s\n", arg);
		ft_putstr_fd("Minishell: error: malloc failed\n", STDERR_FILENO);
		ms->exit = 12;
		free(ms);
		exit(ms->exit);
	}
	if (op == 3 && arg != NULL)
	{
		printf("error in: %s\n", arg);
		exit(ms->exit);
	}
}

int	open_error(t_minishell *ms, char *filename, int child)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	perror(filename);
	if (filename)
		free(filename);
	if (child)
	{
		ms->exit = 1;
		free_ms(ms);
	}
	else
		return (1);
	return (0);
}

void	pipe_error(t_minishell *ms, int *pipe_fd)
{
	close_fd(pipe_fd);
	ft_putstr_fd("Minishell: error: pipe failed\n", STDERR_FILENO);
	ms->exit = 1;
	free_ms(ms);
}

void	fork_error(t_minishell *ms, int *pipe_fd)
{
	close_fd(pipe_fd);
	ft_putstr_fd("Minishell: error: fork failed\n", STDERR_FILENO);
	ms->exit = 1;
	free_ms(ms);
}
