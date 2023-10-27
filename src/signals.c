/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:11:59 by dimarque          #+#    #+#             */
/*   Updated: 2023/10/27 17:43:14 by dimarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_C(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_init(void)
{
	signal(SIGINT, signal_C);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_D(t_minishell *ms)
{
	if (!(ms->input))
	{
		write(2, "\033[1;31mexit!\033[0m\n", 17);
		free_ms(ms);
	}
}
