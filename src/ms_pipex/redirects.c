#include "../../inc/minishell.h"

int	redirect_in(t_minishell *ms, char *file, int heredoc, int child)
{
	int		fd;
	char	*file_buf;

	file_buf = remove_quotes(file);
	fd = open(file_buf, O_RDONLY);
	if (fd < 0)
		return (open_error(ms, file_buf, child));
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		if (heredoc)
			unlink(file_buf);
	}
	free(file_buf);
	return (0);
}

void	reset_fds(t_minishell *ms)
{
	dup2(ms->fdout_buf, STDOUT_FILENO);
	close(ms->fdout_buf);
	dup2(ms->fdin_buf, STDIN_FILENO);
	close(ms->fdin_buf);
}

int	redirect(t_minishell *ms, char **main_arr, int pos, int child)
{
	int	index;
	int	error;

	index = pos;
	error = 0;
	while (main_arr[index] && main_arr[index][0] && ft_strcmp(main_arr[\
		index], "|") != 0)
	{
		if (ft_strcmp(main_arr[index], "<") == 0)
			error = redirect_in(ms, main_arr[index + 1], 0, child);
		else if (ft_strcmp(main_arr[index], "<<") == 0)
			error = redirect_in(ms, main_arr[index + 1], 1, child);
		else if (ft_strcmp(main_arr[index], ">") == 0)
			error = redirect_out(ms, main_arr[index + 1], 0, child);
		else if (ft_strcmp(main_arr[index], ">>") == 0)
			error = redirect_out(ms, main_arr[index + 1], 1, child);
		index++;
		if (error)
			return (1);
	}
	return (0);
}
