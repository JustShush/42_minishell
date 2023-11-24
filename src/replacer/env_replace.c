/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:54:16 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/18 18:54:16 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*replace_dollar(t_minishell *ms, char *str, char *buf, int flag)
{
	char	*res;
	char	*buf1;
	char	*buf2;

	buf2 = NULL;
	if (str[0] && str[1] && str[0] == '$' && str[1] == '?')
		return (dollar_cond(ms, buf));
	if (ft_strcmp(str, "$") == 0 || (str[1] && !ft_isalnum(str[1])
			&& str[1] != '_' && str[1] != '\\') || str[1] == '?')
		return (ft_strjoin(buf, str));
	buf1 = ft_strtrim(str, "$");
	buf2 = replace_str(ms, buf1);
	free(buf1);
	if (flag == 2)
	{
		buf1 = ft_strdup(buf2);
		free(buf2);
		buf2 = add_quotes(buf1, '\'');
		free(buf1);
	}
	res = ft_strjoin(buf, buf2);
	free(buf2);
	return (res);
}

char	*replace_quotes(t_minishell *ms, char *str, char *buf, int flag)
{
	char	*res;
	char	*buf1;

	res = NULL;
	buf1 = NULL;
	if (str[0] == '\'' && ft_strcmp(str, "\'\'") != 0)
		res = replace_single(ms, str, buf, flag);
	else if (str[0] == '\"' && ft_strcmp(str, "\"\"") != 0)
	{
		res = remove_quotes(str, '\"');
		buf1 = replacer(ms, res, 1);
		free(res);
		res = ft_strjoin(buf, buf1);
	}
	else
		res = ft_strjoin(buf, str);
	free(buf1);
	return (res);
}

char	*replace_cond(t_minishell *ms, char *str, char *buf1, int flag)
{
	char	*res;
	char	*buf2;

	res = NULL;
	buf2 = NULL;
	if (str[0] == '$')
		res = replace_dollar(ms, str, buf1, flag);
	else if (parser_op(str[0]) == 3)
		res = replace_quotes(ms, str, buf1, flag);
	else if (flag == 2)
	{
		buf2 = add_quotes(str, '\'');
		res = ft_strjoin(buf1, buf2);
		free(buf2);
	}
	else
		res = ft_strjoin(buf1, str);
	return (res);
}

char	*replace_loop(t_minishell *ms, char **arr, int flag)
{
	int		i;
	char	*res;
	char	*buf1;

	i = 0;
	res = NULL;
	buf1 = NULL;
	while (arr[i])
	{
		buf1 = ft_strdup(res);
		free(res);
		if (flag == 0 && arr_size(arr) >= 2 && ft_strcmp(arr[i], "$") == 0 \
			&& arr[i + 1] && arr[i + 1][0] && (arr[i + 1][0] == '\'' 
			|| arr[i + 1][0] == '\"'))
			res = NULL;
		else if (arr_size(arr) != 1 && (ft_strcmp(arr[i], "\"\"") == 0
				|| ft_strcmp(arr[i], "\'\'") == 0))
			res = ft_strdup(buf1);
		else
			res = replace_cond(ms, arr[i], buf1, flag);
		free(buf1);
		i++;
	}
	return (res);
}

//Joins all substituted strings from the split str
char	*replacer(t_minishell *ms, char *str, int flag)
{
	char	*res;
	char	**arr;

	arr = var_split(str);
	if (!arr)
		return (NULL);
	res = replace_loop(ms, arr, flag);
	free_arr(arr);
	return (res);
}

int	env_var(t_minishell *ms)
{
	int		i;
	int		size;
	char	*buf;

	i = 0;
	size = arr_size(ms->main_arr);
	if (empty_var(ms->main_arr, ms->env))
		return (1);
	while (i < size)
	{
		buf = ft_strdup(ms->main_arr[i]);
		free(ms->main_arr[i]);
		ms->main_arr[i] = replacer(ms, buf, 0);
		if (!ms->main_arr[i])
			error(ms, 2, "env_var");
		free(buf);
		i++;
	}
	return (0);
}
