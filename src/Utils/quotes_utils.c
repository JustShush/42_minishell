/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 12:49:04 by dimarque          #+#    #+#             */
/*   Updated: 2024/01/24 12:49:04 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quote_num(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (parser_op(str[i]) == 3)
		{
			i = skip_quotes(str, i);
			n += 2;
		}
		else
			i++;
	}
	return (n);
}

int	skip_quotes(char *str, int pos)
{
	char	quote;

	if (parser_op(str[pos]) == 3)
	{
		quote = str[pos++];
		while (str[pos] && str[pos] != quote)
			pos++;
		pos++;
	}
	return (pos);
}

//Removes quotes from str. Used for case echo "'$HOME'"
char	*remove_quotes(char *str)

{
	int		i;
	int		j;
	char	*buf;
	char	quote;

	i = 0;
	j = 0;
	buf = ft_calloc(sizeof(char), (ft_strlen(str) - quote_num(str) + 1));
	while (str[i])
	{
		if (parser_op(str[i]) == 3)
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				buf[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			buf[j++] = str[i++];
	}
	return (buf);
}

char	*add_quotes(char *str, char c)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	buf = calloc(sizeof(char), ft_strlen(str) + 3);
	buf[j++] = c;
	while (str[i])
		buf[j++] = str[i++];
	buf[j] = c;
	return (buf);
}

//Removes quotes from str.
void	rm_quotes(char *str)
{
	char *src = str;
	char *dst = str;

	while (*src) {
		if (parser_op(*src) == 3) {
			src++;
		} else {
			*dst++ = *src++;
		}
	}

	*dst = '\0';
}

void	rm_all_quotes(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i])
	{
		rm_quotes(cmds[i]);
		i++;
	}
}
