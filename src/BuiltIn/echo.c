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

char	*if_rm_quots(char *str)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 1;
	len = (int)ft_strlen(str) - 2;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	if (!str)
		return (NULL);
	while (j <= len) 
	{
		new[i] = str[j];
		i++;
		j++;
	}
	new[i] = '\0';
	len = (int)ft_strlen(new);	
	free(str);
	return (new);
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
