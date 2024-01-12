/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-avel <mde-avel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:31:15 by dimarque          #+#    #+#             */
/*   Updated: 2024/01/12 14:47:25 by mde-avel         ###   ########.fr       */
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
	char	**cmds;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_minishell
{
	char	*prompt;
	char	*input;
	char	**history;
	char	**main_arr;
	int		exit;
	int		cmd_count;
	t_list	**env;
	t_cmdlist	*cmdlist;
}	t_minishell;

//* ---- src DIR ----

//! in main.c
void	minishell(t_minishell *ms);
t_list	**env_init(char **envp);

//! in frees.c
void	free_list(t_list **list);
void	free_cmd_list(t_cmdlist *cmdlist);
void	free_arr(char **arr);
void	free_ms(t_minishell *ms);

//! in prompt.c
//char	*prompt(void);

//! in signals.c
void	signal_C(int signum);
void	signal_process_interrupt(int signum);
void	signal_init(void);
void	signal_D(t_minishell *ms);
void	post_process_signal(void);

//* ---- BuiltIn DIR ----

//! in cd.c
char	*var_str(t_list *env, char *var);
void	go_home(t_minishell *ms);
void	cd(t_minishell *ms, char **path);

//! in echo.c
int		check_option(char *opt);
void	command_echo(char **cmd_line, int flag, int i);
void	echo(char **cmd_line);

//! in env.c
void	env(t_minishell *ms, char **cmd_line);

//! in exit.c
void	ft_exit(t_minishell *ms, char **path);

//! in export.c
int		ft_identifier(char	*s);
int		find_ident_exp(t_list **env, char *content, char *new_cont);
int		check_identifier(t_minishell *ms, char *content);
void	print_exp(t_list **lst);
void	ft_export(t_minishell *ms, char **cmd_line);

//! in pwd.c
void	pwd(void);

//! in unset.c
void	rm_first_last(t_list **env);
void	remove_node(t_list **env, char *ident, size_t len);
void	find_ident_unset(t_list **env, char *ident2);
void	unset(t_minishell *ms, char **cmd_line);

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
int		dolar(char *str, int i);
int		others(char *str, int i);

//* --- Replacer DIR ----
//! in env_replacer.c

char	*replace_cond(t_minishell *ms, char *str, char *buf1, int flag);

/** Joins all substituted strings from the split str
 * @param string The string with all the vars
 * @param env env struct
 * @param flag
 * @return The new string now with the value of the var.
*/
char	*replacer(t_minishell *ms, char *str, int flag);

/**
 * This replaces all the Vars to their actuall value.
 * @param ms The minishell main Struct
 * @param env env struct
 * @param arr Main Array with all the inputs
*/
int	env_var(t_minishell *ms);

//! in env_split_utils.c

char	*dollar_cond(t_minishell *ms, char *buf);
char	*var_iter(t_list **env, char *var);
char	*var_str(t_list *env, char *var);
int		empty_var(char **arr, t_list **env);

//! in env_split.c

char	**var_split(char *str);

//! in env_split2.c
char	*replace_str(t_minishell *ms, char *str);
char	*replace_single(t_minishell *ms, char *str, char *buf, int flag);

//* ---- Utils DIR ----

//! in arr_size.c
int		arr_size(char **arr);

//! in check_cmd.c
int		IsBuiltIn(char *str);
void	builtIn(t_minishell *ms, char **cmd_flags);
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
 */
void	error(t_minishell *ms, int op, char *arg);

//! in inits.c

int	var_init(t_minishell *ms);

//! in quotes_utils.c

int		skip_quotes(char *str, int pos);
char	*add_quotes(char *str, char c);
char	*remove_quotes(char *str, char c);
int		closed_quotes(char *str, char c);

//! in str_utils.c

int	strlen_chr(char *str, char c);
int	strchr_malloc(char *s, char c);
char	*str_front_trim(char *str, char *trim);
int	strcmp_nochr(char *s1, char *s2, char c);

#endif