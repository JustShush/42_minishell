/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:31:15 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/17 17:41:31 by dimarque         ###   ########.fr       */
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
	t_list	**env;
	t_cmdlist	*cmdlist;
}	t_minishell;


//! in frees.c
void	free_ms(t_minishell *ms);
void	free_arr(char **arr);

//! in prompt.c
char	*prompt(void);

//! in signals.c
void	signal_init(void);
void	signal_D(t_minishell *ms);

//* ---- BuiltIn DIR ----

//! in cd.c
char	*var_str(t_list *env, char *var);
void	go_home(t_minishell *ms);
void	cd(t_minishell *ms, char **path);

//! in echo.c
void	echo();

//! in env.c
void	env();

//! in exit.c
void	ft_exit();

//! in export.c
void	ft_export();

//! in pwd.c
void	pwd(void);

//! in unset.c
void	unset();

//* ---- Parser DIR ----

//! in ms_split.c
char	**ms_split(char *str);

//! in parser_utils.c
int		quotes(char *str, char c, int i);
int		space_tab(char *str, int i);
int		dolar(char *str, int i);
int		others(char *str, int i);

//* ---- Other DIR ----

//! in print_env.c

void	print_env(char **env);

//* ---- Utils DIR ----
//! in arr_size.c

int		arr_size(char **arr);
void	check_cmd(t_minishell *ms);
//! in error.c

/**
 * @param op type of error msg
 * @param arg (optional) addicional msg
 */
void	error(int op, char *arg);

#endif