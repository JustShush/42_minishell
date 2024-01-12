/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:31:11 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/17 16:31:11 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/minishell.h"

void	go_home(t_minishell *ms)
{
	char	*home;

	home = ft_strtrim(var_str(*ms->env, "HOME="), "HOME=");
	if (!home)
	{
		write(2, "Minishell$> cd: HOME is undefined\n", 34);
		ms->exit = 1;
		exit (1);
	}
	else if (chdir(home) != 0)
	{
		perror("Minishell$> cd: HOME");
		ms->exit = 1;
		exit (1);
	}
	if (home)
		free(home);
}

void	cd(t_minishell *ms, char **path)
{
	char	old_pwd[PATH_MAX + 1];

	getcwd(old_pwd, sizeof(old_pwd));
	if (path && arr_size(path) > 2)
	{
		write(2, "Minishell$> cd: too many arguments\n", 35);
		ms->exit = 1;
		ft_bzero(old_pwd, ft_strlen(old_pwd));
		return ;
	}
	// if theres is no arg (ex: cd) just return to home
	else if (!path || !path[1] || !path[1][0])
		go_home(ms);
	else if (chdir(path[1]) == -1)
	{
		perror("Minishell$> cd");
		ms->exit = 1;
		return ;
	}
	// Use the chdir function to change the current working directory
}

//* if there is no loc go back to home. DONE!
// TODO: check if path is a valid dir