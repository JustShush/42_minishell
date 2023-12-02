/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-avel <mde-avel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:31:15 by dimarque          #+#    #+#             */
/*   Updated: 2023/12/01 17:58:40 by mde-avel         ###   ########.fr       */
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

# include <sys/ioctl.h>

typedef struct s_content
{
	t_list	content;
	char	**cmd_flags;
}	t_content;

typedef struct s_cmdlist
{
	t_content	*content;
	struct s_cmdlist	*next;
}	t_cmdlist;

typedef struct s_minishell
{
	char	*prompt;
	char	*input;
	char	**history;
	char	**main_arr;
	int		exit;
	t_list	**env;
	t_cmdlist	*cmdlist;
}	t_minishell;

//* ---- src DIR ----

//! in main.c
void	minishell(t_minishell *ms);
t_list	**env_init(char **envp);

//! in frees.c
void	free_list(t_list **list);
void	free_arr(char **arr);
void	free_ms(t_minishell *ms);

//! in prompt.c
//char	*prompt(void);

//! in signals.c
void	signal_C(int signum);
void	signal_init(void);
void	signal_D(t_minishell *ms);

//* ---- BuiltIn DIR ----

//! in cd.c
char	*var_str(t_list *env, char *var);
void	go_home(t_minishell *ms);
void	cd(t_minishell *ms, char **path);

//! in echo.c
int		check_option(char *opt);
void	echo(char **cmd_line);

//! in env.c
void	env(t_minishell *ms, char **cmd_line);

//! in exit.c
void	ft_exit(t_minishell *ms, char **path);

//! in export.c
int		ft_identifier(char	*s);
int		find_ident(t_list **env, char *content, char *new_cont);
int		check_identifier(t_minishell *ms, char *content);
void	ft_export(t_minishell *ms, char **cmd_line);

//! in pwd.c
void	pwd(void);

//! in unset.c
void	unset(void);

//* ---- Other DIR ----

//! in print_env.c
void	print_env(char **env);

//* ---- Parser DIR ----

//! in ms_split.c
int		parser_op(char c);
int		countw(char *str);
char	*split_temp(char *str, int word_len);
int		get_wordl(char *str);
char	**ms_split(char *str);

//! in parser_utils.c
int		quotes(char *str, char c, int i);
int		space_tab(char *str, int i);
int		dolar(char *str, int i);
int		others(char *str, int i);

//* ---- Utils DIR ----

//! in arr_size.c
int		arr_size(char **arr);

//! in check_cmd.c
int		IsBuiltIn(char *str);
void	builtIn(t_minishell *ms, char **cmd_flags);
void	check_cmd(t_minishell *ms);

//! in error.c
/**
 * @param op type of error msg
 * @param arg (optional) addicional msg
 */
void	error(int op, char *arg);

#endif