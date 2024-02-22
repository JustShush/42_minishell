/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:46:19 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/17 10:46:19 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_option(char *opt)
{
	int		i;
	int		len;
	char	*str;

	if (!opt)
		return (0);
	if (ft_strcmp(opt, "-n") == 0)
		return (1);
	i = 1;
	str = ft_strdup(opt);
	len = (int)ft_strlen(opt);
	str[0] = '-';
	while (i < len)
	{
		str[i] = 'n';
		i++;
	}
	if (ft_strcmp(opt, str) == 0)
	{
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

//printf("cmd: |%s| c: %c\n", new_cmd, new_cmd[len]);
//printf("new: |%s| c: %c \n", new_cmd, new_cmd[len]);
char	*if_quot_marks(char *cmd_line)
{
	char	*new_cmd;
	int		len;

	new_cmd = ft_strdup(cmd_line);
	len = ft_strlen(new_cmd) - 1;
	while (1)
	{
		if ((new_cmd[0] == '"' && new_cmd[len] == '"') || 
			(new_cmd[0] == '\'' && new_cmd[len] == '\''))
		{
			new_cmd = rm_quots(new_cmd);
			len = ft_strlen(new_cmd) - 1;
		}
		else
			break ;
	}
	return (new_cmd);
}

void	with_option(char **cmd_line, int i)
{
	char	*new_cmd;

	while (cmd_line[i])
	{
		new_cmd = if_quot_marks(cmd_line[i]);
		if (new_cmd == NULL)
			ft_printf("%s", cmd_line[i]);
		else
		{
			ft_printf("%s", new_cmd);
			free(new_cmd);
		}
		if (cmd_line[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
}

void	no_option(char **cmd_line)
{
	int		i;
	char	*new_cmd;

	i = 1;
	while (cmd_line[i])
	{
		new_cmd = if_quot_marks(cmd_line[i]);
		if (new_cmd == NULL)
			ft_printf("%s ", cmd_line[i]);
		else
		{
			ft_printf("%s ", new_cmd);
			free(new_cmd);
		}
		i++;
	}
	ft_printf("\n");
}

//echo -n -n -nnnnn    "banana   .  "
void	myecho(char **cmd_line)
{
	int	i;
	int	flag;

	if (!cmd_line[1])
		return ;
	flag = 0;
	i = 1;
	if (check_option(cmd_line[i]) == 1)
	{
		flag = 1;
		i++;
	}
	if (flag)
		with_option(cmd_line, i);
	else
		no_option(cmd_line);
}
