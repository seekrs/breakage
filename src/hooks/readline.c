/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 07:21:42 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 07:21:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

char	*readline(const char *prompt)
{
	char	*line;
	int		state;

	brk_find_symbol("readline", (void **)&g_real_readline);
	state = g_brk_hook_enable;
	g_brk_hook_enable = 0;
	line = g_real_readline(prompt);
	g_brk_hook_enable = state;
	return (line);
}
