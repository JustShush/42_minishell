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
		return (1);
	free(str);
	return (0);
}

//ft_printf("%snew_cmd:%s|%s|\n", PURPLE, RESET, cmd_line[i]);
char	*quot_marks(char *cmd_line)
{
	size_t	len;
	char	*new_cmd;

	len = ft_strlen(cmd_line) - 1;
	if (cmd_line[0] == '"' && cmd_line[len] == '"')
	{
		new_cmd = ft_strtrim(cmd_line, "\"");
	}
	else
		return (NULL);
	return (new_cmd);
}

void	with_option(char **cmd_line, int i)
{
	char	*new_cmd;

	ft_printf("%swith_option:%s\n", PURPLE, RESET);
	while (cmd_line[i])
	{
		new_cmd = quot_marks(cmd_line[i]);
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

//echo hello "banana    minion gosta"
void	no_option(char **cmd_line)
{
	int i;
	char	*new_cmd;

	i = 1;
	ft_printf("%sno_option:%s\n", BLUE, RESET);
	while (cmd_line[i])
	{
		new_cmd = quot_marks(cmd_line[i]);
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

void	echo(char **cmd_line)
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
