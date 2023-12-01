/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimarque <dimarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:11:59 by dimarque          #+#    #+#             */
/*   Updated: 2023/12/01 15:13:32 by dimarque         ###   ########.fr       */
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

void	signal_process_interrupt(int signum)
{
	if (signum == SIGQUIT)
		g_global = SIGQUIT;
	if (signum == SIGINT)
		g_global = SIGINT;
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
		free_ms(ms); // TODO: problem here with free_ms main_arr
	}
}

void	post_process_signal(void)
{
	if (!g_global)
		return ;
	if (g_global == SIGQUIT)
		ft_putstr_fd("Quit\n", STDERR_FILENO);
	if (g_global == SIGINT)
		printf("\n");
	g_global = 0;
}
