/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:31:15 by dimarque          #+#    #+#             */
/*   Updated: 2023/11/03 16:32:25 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "header.h"

# include "../libft/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <limits.h> // PATH_MAX
# include <signal.h>

# include <sys/ioctl.h>

typedef struct s_minishell
{
	char	*prompt;
	char	*input;
	char	**history;
	char	**main_arr;
}	t_minishell;


// in frees.c

void	free_ms(t_minishell *ms);
void	free_arr(char **arr);
// -------------------

// in prompt.c

char	*prompt(void);
// -------------------

// in signals.c

void	signal_init(void);
void	signal_D(t_minishell *ms);
// -------------------

// ---- Other DIR ----
// in ms_split.c

char	**ms_split(char *str);
// in print_env.c

void	print_env(char **env);
// -------------------

// ---- Utils DIR ----
// in error.c

void	error(int op, char *arg);
// -------------------

#endif