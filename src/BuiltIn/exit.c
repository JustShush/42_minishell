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
		write(2, "Minishell$> exit: too many arguments\n", 37);
		free_ms(ms);
		exit(1);
	}	
	else
	{
		free_ms(ms);
		exit(0);
	}
}
//should release all allocated memory