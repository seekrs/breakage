/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk_backtrace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:33:05 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 02:18:44 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

void	brk_backtrace(void)
{
	void	*buffer[100];
	int		nptrs;
	char	**strings;
	int		j;
	int		state;

	state = g_brk_hook_enable;
	g_brk_hook_enable = 0;
	nptrs = backtrace(buffer, 100);
	strings = backtrace_symbols(buffer, nptrs);
	g_brk_hook_enable = state;
	if (strings == NULL)
	{
		brk_log(WARN, "failed to backtrace\n");
		return ;
	}
	brk_log(INFO, "Obtained %d stack frames.\n", nptrs);
	j = 0;
	while (j < nptrs)
	{
		brk_fprintf(stderr, "\t%s\n", strings[j]);
		j++;
	}
	g_real_free(strings);
}
