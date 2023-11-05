/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:00:23 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/03 16:57:39 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	return ((c == ' ' || c == '\t'));
}

// spaces" "; pipes | ; dolar $; single '; double ";
int	countw(char *str)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str && str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i] && (str[i] != ' ' || str[i] != '\t'))
			words++;
		if (str[i] && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
			i = others(str, i);
		else if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			i = quotes(str, str[i], i);
		else if (str[i] && str[i] == '$')
			i = dolar(str, i);
		else if (str[i] && (str[i] != ' ' || str[i] != '\t'))
			i = space_tab(str, i);
	}
	return (words);
}

char	*split_temp(char *str, int word_len)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (word_len + 1));
	if (!temp)
		error(1, NULL);
	while (*str && i < word_len)
		temp[i++] = *str++;
	temp[i] = '\0';
	return (temp);
}

int	get_wordl(char *str)
{
	int	i;

	i = 0;
	if (str[i] && (str[i] == '\'' || str[i] == '\"'))
		return (quotes(str, str[i], i));
	if (str[i] && (str[i] == '>' || str[i] == '<' || str[i] == '|'))
		return (others(str, i));
	if (str[i] && str[i] == '$')
		return (dolar(str, i));
	if (str[i] && (str[i] != ' ' || str[i] != '\t'))
		return (space_tab(str, i));
	return (i);
}

char	**ms_split(char *str)
{
	char	**token;
	int		word_len;
	int		i;
	int		j;

	word_len = 0;
	i = 0;
	j = 0;
	if (!(token = malloc(sizeof(char *) * (countw(str) + 1))))
		return (0);
	while (i < countw(str))
	{
		while (*str && ft_isspace(*str))
			str++;
		word_len = get_wordl(str);
		//printf("len: %d\n", word_len);
		token[j++] = split_temp(str, word_len);
		str = str + word_len;
		word_len = 0;
	}
	token[j] = 0;
	return (token);
}
