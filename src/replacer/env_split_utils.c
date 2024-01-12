#include "../../inc/minishell.h"

char	*dollar_cond(t_minishell *ms, char *buf)
{
	char	*buf1;
	char	*res;

	res = NULL;
	buf1 = ft_itoa(ms->exit);
	res = ft_strjoin(buf, buf1);
	free(buf1);
	return (res);
}

//Compares env variables with var.
//Returns the value of var if it finds it in env.
// var = HOME
// env: HOME=home/just
// return: home/just
char	*var_cmp(char *env, char *var)
{
	char	*buf1;
	char	*buf2;

	if (strcmp_nochr(var, env, '=') == 0)
	{
		buf1 = str_front_trim(env, var);
		buf2 = str_front_trim(buf1, "=");
		free(buf1);
		return (buf2);
	}
	return (NULL);
}

char	*var_iter(t_list **env, char *var)
{
	char	*buf;
	t_list	*tmp;

	tmp = *env;
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

int	empty_var(char **arr, t_list **env)
{
	char	*buf1;
	char	*buf2;

	if (arr_size(arr) == 1 && strchr_malloc(arr[0], '$') 
		&& ft_strcmp(arr[0], "$") != 0 && ft_strcmp(arr[0], "$?") != 0)
	{
		buf1 = str_front_trim(arr[0], "$");
		buf2 = var_iter(env, buf1);
		free(buf1);
		if (!buf2)
		{
			free(buf2);
			return (1);
		}
		free(buf2);
	}
	return (0);
}