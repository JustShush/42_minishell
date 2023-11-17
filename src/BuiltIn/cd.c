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

// equivalent to 'env | grep var'
char	*var_str(t_list *env, char *var)
{
	t_list	*tmp;

	tmp = env;
	while (tmp->content)
	{
		if (ft_strncmp((char *)tmp->content, var, ft_strlen(var)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp->content);
}

void	go_home(t_minishell *ms)
{
	char	*home;

	home = ft_strtrim(var_str(*ms->env, "HOME="), "HOME=");
	if (!home)
	{
		write(2, "Minishell$> cd: HOME is undefined\n", 34);
		exit (1);
	}
	else if (chdir(home) != 0)
	{
		perror("Minishell$> cd: HOME");
		exit (1);
	}
	if (home)
		free(home);
}

void	cd(t_minishell *ms, char **path)
{
	char	old_pwd[PATH_MAX + 1];
	char	*tmp;
	char	*new_path;
	int		

	getcwd(old_pwd, sizeof(old_pwd));
	if (path && arr_size(path) > 2)
	{
		write(2, "Minishell: cd: too many arguments\n", 34);
		ft_bzero(old_pwd, ft_strlen(old_pwd));
		return ;
	}
	// if theres is no arg (ex: cd) just return to home
	else if (!path || !path[1] || !path[1][0])
		go_home(ms);
	else if (chdir(path[1]) != 0)
	{
		perror("Minishell$> cd");
		return ;
	}
	// Use the chdir function to change the current working directory
	if (old_pwd != NULL)
	{
		if (chdir(old_pwd) != 0)
			perror("Minishell$> cd Error!");
		free(old_pwd);
		//exit
	}
	if (execve(path, ms->main_arr, ms->env) == -1)
	{
		if (ms->main_arr[1])
		{
			tmp = ft_strjoin(old_pwd, "/");
			new_path = ft_strjoin(tmp, ms->main_arr[1]);
			free(tmp);
			if (access(new_path, F_OK) == -1)
				printf("Minishell$> cd: %s: No such file or directory\n", ms->main_arr[1]);
			free(new_path);
		}
		printf("Minishell$> Falier to execute\n");
		free(old_pwd);
	}
}

//* if there is no loc go back to home. DONE!
// TODO: check if path is a valid dir