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

void	ft_exit(t_minishell *ms)
{
	free_ms(ms);
	if (ms->exit >= 0 && ms->exit <= 255)
	{
		perror("Minishell$> exit");
		exit(ms->exit);
	}
}
//should release all allocated memory