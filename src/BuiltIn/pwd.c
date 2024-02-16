/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:30 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/17 10:46:30 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//for unset & export
int	ft_identifier(char	*s)
{
	int	i;
	int	flag;

	if (ft_strcmp(s, "_") == 0)
		return (2);
	if ((s[0] >= '0' && s[0] <= '9') || s[0] == '=')
		return (0);
	i = 0;
	flag = 0;
	while (s[i])
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= '0' && s[i] <= '9')
			|| (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
			flag = 1;
		else
		{
			flag = 0;
			break ;
		}
		i++;
	}
	if (flag == 1)
		return (1);
	return (0);
}

void	pwd(void)
{
	int		i;
	char	cwd[PATH_MAX + 1];

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL) 
	{
		printf("%s\n", cwd);
		while (cwd[i])
			cwd[i++] = 0;
	}
	else
		perror("Minishell$> pwd() error!");
}
