#include "../../inc/minishell.h"

//Removes quotes from str. Used for case echo "'$HOME'"
void	rm_quotes(char *str)
{
	char *src = str;
	char *dst = str;

	while (*src) {
		if (*src == '"' || *src == '\'') {
			src++;
		} else {
			*dst++ = *src++;
		}
	}

	*dst = '\0';  // Null-terminate the modified string
}
