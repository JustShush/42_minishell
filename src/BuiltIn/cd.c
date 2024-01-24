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

//printf("dir: %s\n", pwd);
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
			ft_bzero(pwd, ft_strlen(pwd));
			free((tmp)->content);
			(tmp)->content = ident;
			break ;
		}	
		tmp = (tmp)->next;
	}
}

void	home_to_dir(t_minishell *ms, char *path)
{
	size_t	len;
	char *new_path;

	len = ft_strlen(path) - 2;
	new_path = ft_substr(path, 2, len);
	if (chdir(new_path) == -1)
	{
		error_message(ms, "cd: No such file or directory\n", new_path);
		ms->exit = 1;
	}
	free(new_path);
}

int	find_home(t_list **lst)
{
	t_list	*tmp;

	tmp = *lst;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (ft_strncmp((char *)(tmp)->content, "HOME=", 4) == 0)
			return(1);	
		tmp = (tmp)->next;
	}
	return (0);
}

void	go_home(t_minishell *ms)
{
	char	*home;

	if (find_home(ms->env) == 0)
	{
		error_message(ms, "cd: HOME not set\n", NULL);
		ms->exit = 1;
	}
	else
	{
		home = ft_strtrim(var_str(*ms->env, "HOME="), "HOME=");
		if (chdir(home) == -1)
		{
			error_message(ms, "cd: No such file or directory\n", NULL);
			ms->exit = 1;
		}
		free(home);
	}		
}

void	cd(t_minishell *ms, char **path)
{
	if (path && arr_size(path) > 2)
	{
		error_message(ms, "cd: too many arguments\n", NULL);
		ms->exit = 1;
	}
	else if (!path || !path[1] || path[1][0] == '~')
	{
		go_home(ms);
		if (path[1][1] == '/' && path[1][2])
			home_to_dir(ms, path[1]);
	}
	else if (chdir(path[1]) == -1)
	{
		error_message(ms, "cd: No such file or directory\n", path[1]);
		ms->exit = 1;
	}
	change_dir(ms->env);
}
// cd ~ -> home
// if theres is no arg (ex: cd) just return to home
// Use the chdir function to change the current working directory
//* if there is no loc go back to home. DONE!
// TODO: check if path is a valid dir
