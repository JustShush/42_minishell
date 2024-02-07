/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-avel <mde-avel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:31:15 by dimarque          #+#    #+#             */
/*   Updated: 2024/02/07 15:26:25 by mde-avel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "header.h"

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <limits.h> // PATH_MAX
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>

# include <stddef.h>
# include <sys/ioctl.h>

extern int	g_global;

typedef struct s_content
{
	t_list	content;
	char	**cmd_flags;
}	t_content;

typedef struct s_cmdlist
{
	char				**cmds;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_minishell
{
	char		*prompt;
	char		*input;
	char		**history;
	char		**main_arr;
	int			exit;
	int			cmd_count;
	int			fdin;
	int			fdout;
	int			dp[2];
	int			cmd_fd;
	t_list		**env;
	t_cmdlist	*cmdlist;
}	t_minishell;

//* ---- src DIR ----

//! in main.c
void	minishell(t_minishell *ms);
t_list	**env_init(char **envp);

//! in frees.c
void	close_fd(int *fd);
void	free_list(t_list **list);
void	free_cmd_list(t_cmdlist *cmdlist);
void	free_arr(char **arr);
void	free_ms(t_minishell *ms);

//! in prompt.c
//char	*prompt(void);

//! in signals.c
void	signal_c(int signum);
void	signal_process_interrupt(int signum);
void	signal_init(void);
void	signal_d(t_minishell *ms);
void	post_process_signal(void);

//* ---- BuiltIn DIR ----

//! builtin_utils.c
char	*env_strchr(const char *str, int c);
t_list	*ft_envnew(void *content);

//! in cd.c
void	go_home(t_minishell *ms);
void	cd(t_minishell *ms, char **path);

//! in echo.c
int		check_option(char *opt);
void	command_echo(char **cmd_line, int flag, int i);
void	echo(char **cmd_line);

//! in env.c
void	print_lst(t_list **lst, int flag);
void	env(t_minishell *ms, char **cmd_line);

//! in exit.c
int		check_if_num(t_minishell *ms, char *arg);
int		calc_exit(int n);
void	ft_exit(t_minishell *ms, char **path);

//! in export.c
int		ft_identifier(char	*s);
int		find_ident_exp(t_list **env, char *content, char *new_cont, int flag);
int		check_identifier(t_minishell *ms, char *content);
void	print_exp(t_list **lst);
void	ft_export(t_minishell *ms, char **cmd_line);

//! in pwd.c
int		ft_identifier(char	*s);
void	pwd(void);

//! in unset.c
void	rm_first_last(t_list **env);
void	remove_node(t_list **env, char *ident, size_t len);
void	find_ident_unset(t_list **env, char *ident2);
void	unset(t_minishell *ms, char **cmd_line);

//* ---- ms_pipex DIR ----
//! in exec_utils.c

int		is_exec(t_minishell *ms, char *cmd, char **paths);
int		is_usable(t_minishell *ms, char	*cmd, char *cmd_path, \
char **paths_array);

//! in exec.c

void	exec(t_minishell *ms, char **cmd_arr);

//! in ms_pipex

int		find_cmd_pos(char **main_arr, int pos);
void	get_exit_status(t_minishell *ms, pid_t pid, int cmds_run);
void	child(t_minishell *ms, int *pipe_fd, int cmds_run, int pos);
void	parent(t_minishell *ms, int *pipe_fd, int cmds_run, int pos);

//* ---- Other DIR ----
//! in print_env.c
void	print_env(char **env);

//* ---- Parser DIR ----

//! in ms_split.c

int		parser_op(char c);
int		countw(char *str);
char	*split_temp(t_minishell *ms, char *str, int word_len);
int		get_wordl(char *str);
char	**ms_split(t_minishell *ms, char *str);

//! in parser_utils.c
int		quotes(char *str, char c, int i);
int		space_tab(char *str, int i);
int		envar(char *str, int i);
int		others(char *str, int i);

//* --- Replacer DIR ----
//! in env_split_utils.c

char	*dollar_cond(t_minishell *ms, char *buf);
char	*var_iter(t_minishell *ms, char *var);
char	*var_str(t_list *env, char *var);
int		empty_var(char **arr, t_list **env);

//! in env_split2.c
char	*replace_str(t_minishell *ms, char *str);

//* ---- Syntax DIR ----
//! in syntax_err.c
int		redir_syntax(char *str);
int		double_redir_syntax(char *str);
int		dollar_syntax(char *str);
int		sucession_syntax(char *str);
int		token_syntax(char *str);
int		token_message(char token);

//! in syntax.c
int		syntax_error(t_minishell *ms);

//* ---- Utils DIR ----
//! in arr_utils.c

int		arr_size(char **arr);
char	**ft_arrdup(t_minishell *ms, char **old);
char	**list_to_array(t_minishell *ms, t_list **list);
void	print_arr(char *str, char **arr);

//! in check_cmd.c
int		isbuiltin(char *str);
void	built_in(t_minishell *ms, char **cmd_flags, int parent);
void	check_cmd(t_minishell *ms);

//! in cmd_utils.c

void	print_arr(char *str, char **arr);
void	print_cmdlist(t_cmdlist *cmdlist);
int		cmd_count(char **arr);
char	**cmd_with_flags(t_minishell *ms, char **arr, int pos);

//! in error.c
/**
 * My function to handle all errors
 * @param op type of error msg
 * @param arg (optional) addicional msg
 * @note 2 malloc error, 3 custom error
 */
void	error(t_minishell *ms, int op, char *arg);
void	error_message(t_minishell *ms, char *mess, char *plus);
int		open_error(t_minishell *ms, char *filename, int child);
void	pipe_error(t_minishell *ms, int *pipe_fd);
void	fork_error(t_minishell *ms, int *pipe_fd);

//! in inits.c

int		var_init(t_minishell *ms);

//! in quotes_utils.c

int		skip_quotes(char *str, int pos);
char	*add_quotes(char *str, char c);
char	*remove_quotes(char *str);

//! in redirect.c

void	reset_fds(t_minishell *ms);
int		redirect(t_minishell *ms, char **main_arr, int pos, int child);

//! in str_utils.c

int		strlen_chr(char *str, char c);
int		strchr_malloc(char *s, char c);
char	*str_front_trim(char *str, char *trim);
int		strcmp_nochr(char *s1, char *s2, char c);
char	*ft_strndup(char *str, int len);

char	**replaced_arr(t_minishell *ms);

#endif