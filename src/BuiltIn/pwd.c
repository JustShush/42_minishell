/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:30 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 10:46:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pwd(t_minishell *ms)
{
	int i;
	char cwd[PATH_MAX + 1];

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("%s\n", cwd);
		while (cwd[i])
			cwd[i++] = 0;
	}
	else
	{
		ft_printf("%s%s%s", RED, ms->prompt, RESET);
		perror("pwd() error!");
	}
		
}
