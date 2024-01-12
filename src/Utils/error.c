/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-avel <mde-avel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:58:21 by dimarque          #+#    #+#             */
/*   Updated: 2024/01/12 14:24:02 by mde-avel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	error(t_minishell *ms, int op, char *arg)
{
	if (op == 1 && arg == NULL)
	{
		printf("Malloc error!");
		exit(EXIT_FAILURE);
	}
	if (op == 2)
	{
		printf("%s\n", arg);
		ft_putstr_fd("Minishell: error: malloc failed\n", STDERR_FILENO);
		ms->exit = 12;
		free(ms);
	}
	if (op == 3 && arg != NULL) {
		printf("error in: %s\n", arg);
		exit(EXIT_FAILURE);
	}
}

// funcao error mangmant write->2