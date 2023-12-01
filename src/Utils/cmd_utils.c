#include "../../inc/minishell.h"

void	print_arr(char *str, char **arr)
{
	int	i;
	int	j;

	i = 0;
	if (!arr)
		return ;
	j = arr_size(arr);
	printf("	%s:\n", str);
	while (arr[i] && i < j)
		printf("			%s\n", arr[i++]);
}

void	print_cmdlist(t_cmdlist *cmdlist)
{
	int			i;
	t_cmdlist	*tmp;

	i = 1;
	tmp = cmdlist;
	printf("\nLIST:\n");
	while (tmp)
	{
		printf("	NODE%i:\n", i);
		print_arr("	Command with flags", tmp->cmds);
		i++;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
}

//Counts how many words a command has
int	cmd_args(char **arr, int pos)
{
	int	i;
	int	counter;

	i = pos;
	counter = 0;
	while (arr[i] && !arr[i][0])
		i++;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], ">") == 0 || ft_strcmp(arr[i], ">>") == 0 \
			|| ft_strcmp(arr[i], "<") == 0 || ft_strcmp(arr[i], "<<") == 0)
			i += 2;
		else if (ft_strcmp(arr[i], "|") == 0)
			break ;
		else
		{
			counter++;
			i++;
		}
	}
	return (counter);
}

//Counts how many valid commands there are in main->arr.
int	cmd_count(char **arr)
{
	int	i;
	int	cmd_n;

	i = 0;
	cmd_n = 0;
	while (arr[i])
	{
		cmd_n++;
		while (arr[i] && ft_strcmp(arr[i], "|") != 0)
			i++;
		if (arr[i] && ft_strcmp(arr[i], "|") == 0)
			i++;
	}
	return (cmd_n);
}

//Takes main array and position of a command, and returns an array with the
//command and it's flags
char	**cmd_with_flags(t_minishell *ms, char **arr, int pos)
{
	int		i;
	char	**buf;
	int		args;

	i = 0;
	args = cmd_args(arr, pos);
	buf = malloc(sizeof(char *) * (args + 1));
	if (!buf)
		error(ms, 2, NULL);
	while (arr[pos] && !arr[pos][0])
		pos++;
	while (i < args)
	{
		if (arr[pos] && (ft_strcmp(arr[pos], ">") == 0 \
			|| ft_strcmp(arr[pos], ">>") == 0 || ft_strcmp(arr[pos], "<") == 0 \
			|| ft_strcmp(arr[pos], "<<") == 0))
			pos += 2;
		else if (ft_strcmp(arr[pos], "|") == 0)
			break ;
		else
			buf[i++] = arr[pos++];
	}
	buf[i] = NULL;
	return (buf);
}