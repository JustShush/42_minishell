/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:25 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 10:46:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exit(t_minishell *ms, char **path)
{
	if (path && arr_size(path) > 1)
	{
		error_message(ms, "exit: Too many arguments.\n", NULL);
		free_ms(ms);
		exit(2);
	}	
	else
	{
		free_ms(ms);
		exit(0);
	}
}
//should release all allocated memory