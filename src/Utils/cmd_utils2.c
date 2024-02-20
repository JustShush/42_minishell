/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-avel <mde-avel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 18:54:55 by mde-avel          #+#    #+#             */
/*   Updated: 2024/02/20 19:10:14 by mde-avel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
== Invalid read of size 8
==1300130==    at 0x409977: ft_lstlast (in /home/mde-avel/my_projects/v2_minishell/minishell)
==1300130==    by 0x4092CB: ft_lstadd_back (in /home/mde-avel/my_projects/v2_minishell/minishell)
==1300130==    by 0x403703: cmd_list_init (inits.c:48)
==1300130==    by 0x4037FA: var_init (inits.c:69)
==1300130==    by 0x4015D7: main (main.c:102)
==1300130==  Address 0x4b67bd8 is 8 bytes after a block of size 16 alloc'd
==1300130==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==1300130==    by 0x403588: cmdlist_lstnew (inits.c:21)
==1300130==    by 0x403648: cmd_list_init (inits.c:43)
==1300130==    by 0x4037FA: var_init (inits.c:69)
==1300130==    by 0x4015D7: main (main.c:102)
*/
t_cmdlist	*cmdlist_last(t_cmdlist *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		else
			lst = lst->next;
	}
	return (0);
}

void	cmdlist_add_back(t_cmdlist **lst, t_cmdlist *new)
{
	if (cmdlist_last(*lst))
		cmdlist_last(*lst)->next = new;
	else
		*lst = new;
}
