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

// 0 if not one of the options
int	parser_op(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '<' || c == '>')
		return (2);
	if (c == '\'' || c == '\"')
		return (3);
	if (c == '$')
		return (4);
	return (0);
}

// how many words are in str
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
		else if (str[i] && str[i] == '$')
			i = envar(str, i);
		else if (str[i] && !parser_op(str[i]))
			i = space_tab(str, i);
	}
	return (words);
}

char	*split_temp(t_minishell *ms, char *str, int word_len)
{
	int		i;
	int		j;
	int		flag;
	char	*temp;

	i = 0;
	j = 0;
	flag = 0;
	temp = NULL;
	temp = malloc(sizeof(char) * (word_len + 1));
	if (!temp)
		error(ms, 2, "split_temp", NULL);
	while (str[j] && i < word_len)
	{
		if (flag && parser_op(str[j]) == 3)
		{
			j += 1;
			flag = 0;
		}
		if (parser_op(str[j]) == 3)
			flag = 1;
		temp[i++] = str[j++];
	}
	temp[i] = '\0';
	return (temp);
}

// Returns the length of str until the next whitespace or separating meta-char
int	get_wordl(char *str)
{
	int	i;

	i = 0;
	if (str[i] && parser_op(str[i]) == 3)
		return (quotes(str, str[i], i));
	if (str[i] && parser_op(str[i]) == 2)
		return (others(str, i));
	if (str[i] && parser_op(str[i]) == 4)
		return (envar(str, i));
	if (str[i] && !parser_op(str[i]))
		return (space_tab(str, i));
	return (i);
}

// Splits str into an array of char *
char	**ms_split(t_minishell *ms, char *str)
{
	int		i;
	int		word_len;
	char	**buff;
	int		ms_words;
	char	*string;

	i = 0;
	ms_words = countw(str);
	buff = malloc(sizeof(char *) * (ms_words + 1));
	if (!buff)
		error(ms, 2, "ms_split", NULL);
	while (i < ms_words)
	{
		while (*str && parser_op(*str) == 1)
			str++;
		string = remove_quotes(str);
		word_len = get_wordl(string);
		free(string);
		buff[i++] = split_temp(ms, str, word_len);
		str = str + word_len;
	}
	buff[i] = 0;
	return (buff);
}
