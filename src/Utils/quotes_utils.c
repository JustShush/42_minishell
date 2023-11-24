#include "../../inc/minishell.h"

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

//Removes quotes from str. Used for case echo "'$HOME'"
char	*remove_quotes(char *str, char c)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	i = skip_quotes(str, i);
	buf = calloc(sizeof(char), i);
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != c)
			buf[j++] = str[i++];
		if (str[i] && str[i] == c)
			i++;
	}
	return (buf);
}

// Returns 1 if there are open quotes
// Returns 0 if there are closed quotes
int	closed_quotes(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
	{
		i++;
		while (str[i] && str[i] != c)
			i++;
		i++;
	}
	if (i == (int)ft_strlen(str))
		return (0);
	return (1);
}