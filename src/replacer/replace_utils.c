#include "../../inc/minishell.h"

//Compares env variables with var.
//Returns the value of var if it finds it in env.
// var = HOME
// env: HOME=/home/dmarque
// return: /home/dmarque
char	*var_cmp(char *env, char *var)
{
	char	*buf1;
	char	*buf2;

	if (!var)
		return (NULL);
	if (strcmp_nochr(var, env, '=') == 0)
	{
		buf1 = str_front_trim(env, var);
		buf2 = str_front_trim(buf1, "=");
		free(buf1);
		return (buf2);
	}
	return (NULL);
}

char	*var_iter(t_minishell *ms, char *var)
{
	char	*buf;
	t_list	*tmp;

	if (ft_strcmp(var, "?") == 0)
	{
		buf = ft_itoa(ms->exit);
		return (buf);
	}
	tmp = *ms->env;
	while (tmp)
	{
		buf = var_cmp((char *)tmp->content, var);
		if (buf)
			return (buf);
		tmp = tmp->next;
		free(buf);
	}
	return (NULL);
}

// equivalent to `env | grep var`
char	*var_str(t_list *env, char *var)
{
	t_list	*tmp;

	tmp = env;
	while (tmp->content)
	{
		if (ft_strncmp((char *)tmp->content, var, ft_strlen(var)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp->content);
}
