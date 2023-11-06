/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:46:37 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/06 11:46:37 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quotes(char *str, char c, int i)
{
	if (str[i] && str[i] == c)
	{
		i++;
		while (str[i] && str[i] != c)
			i++;
		if (!str[i])
			return (i);
		i++;
		if (str[i] && (str[i] != ' ' && str[i] != '\t'))
			return (space_tab(str, i));
		else if (str[i] && str[i] == '$')
			return (dolar(str, i));
		else if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			return (quotes(str, str[i], i));
	}
	return (i);
}

int	space_tab(char *str, int i)
{
	if (str[i] && (str[i] != ' ' && str[i] != '\t'))
	{
		while (str[i] && (str[i] != ' ' && str[i] != '\t'))
			i++;
		if (str[i] && str[i] == '$')
			return (dolar(str, i));
		else if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			return (quotes(str, str[i], i));
	}
	return (i);
}

int	dolar(char *str, int i)
{
	if (str[i] == '$')
	{
		i++;
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			return (quotes(str, str[i], i));
		else if (str[i] && (str[i] != ' ' && str[i] != '\t'))
			return (space_tab(str, i));
	}
	return (i);
}

int	others(char *str, int i)
{
	if (str[i] && str[i] == '|')
		i++;
	else if (str[i] == '>')
	{
		i++;
		if (str[i] && (str[i] == '>' || str[i] == '|'))
			i++;
	}
	else if (str[i] == '<')
	{
		i++;
		if (str[i] && (str[i] == '<' || str[i] == '>'))
			i++;
	}
	return (i);
}
