/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:05 by marvin            #+#    #+#             */
/*   Updated: 2023/11/17 10:46:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cd(char *loc)
{
	char cwd[PATH_MAX + 1];

	// Use the chdir function to change the current working directory
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (chdir(cwd) != 0)
			perror("Minishell$> cd Error!");
	}
}

// is there is no loc got back to home.
// check if loc is a valid dir