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

void	change_dir(t_list **lst)
{
	t_list	*tmp;
	char	pwd[PATH_MAX + 1];
	char	*ident;

	ident = "PWD=";
	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (ft_strncmp((char *)(tmp)->content, ident, 4) == 0)
		{
			getcwd(pwd, sizeof(pwd));
			ident = ft_strjoin(ident, pwd);
			free((tmp)->content);
			(tmp)->content = ident;
			break ;
		}	
		tmp = (tmp)->next;
	}
}

void	go_home(t_minishell *ms)
{
	char	*home;

	home = ft_strtrim(var_str(*ms->env, "HOME="), "HOME=");
	if (!home)
	{
		error_message(ms, "cd: HOME is undefined\n", NULL);
		ms->exit = 1;
	}
	else if (chdir(home) == -1)
	{
		error_message(ms, "cd: No such file or directory\n", NULL);
		ms->exit = 1;
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
		error_message(ms, "cd: too many arguments\n", NULL);
		ms->exit = 1;
		ft_bzero(old_pwd, ft_strlen(old_pwd));
	}
	else if (!path || !path[1] || !path[1][0])
		go_home(ms);
	else if (chdir(path[1]) == -1)
	{
		error_message(ms, "cd: No such file or directory\n", NULL);
		ms->exit = 1;
	}
	change_dir(ms->env);
}
// if theres is no arg (ex: cd) just return to home
// Use the chdir function to change the current working directory
//* if there is no loc go back to home. DONE!
// TODO: check if path is a valid dir