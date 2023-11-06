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

// 0 if not one of the options
int	parser_op(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '<' || c == '>' || c == '\t')
		return (2);
	if (c == '\'' || c == '\"')
		return (3);
	if (c == '$')
		return (4);
	return (0);
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
		while (str[i] && parser_op(str[i]) == 1)
			i++;
		if (str[i] && parser_op(str[i]) != 1)
			words++;
		if (str[i] && parser_op(str[i]) == 2)
			i = others(str, i);
		else if (str[i] && parser_op(str[i]) == 3)
			i = quotes(str, str[i], i);
		else if (str[i] && parser_op(str[i]) == 4)
			i = dolar(str, i);
		else if (str[i] && !parser_op(str[i])) // check if its not of the cases here ( \t><|$'")
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
	if (str[i] && parser_op(str[i]) == 3)
		return (quotes(str, str[i], i));
	if (str[i] && parser_op(str[i]) == 2)
		return (others(str, i));
	if (str[i] && parser_op(str[i]) == 4)
		return (dolar(str, i));
	if (str[i] && !parser_op(str[i]))
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
	token = NULL;
	token = malloc(sizeof(char *) * (countw(str) + 1));
	if (!token)
		return (0);
	while (i < countw(str))
	{
		while (*str && parser_op(str[i]) == 1)
			str++;
		word_len = get_wordl(str);
		printf("cw: %d | wlen: %d\n", countw(str), word_len);
		token[j++] = split_temp(str, word_len);
		str = str + word_len;
		word_len = 0;
	}
	token[j] = 0;
	return (token);
}
