/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 07:21:23 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 07:21:26 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

void	add_history(const char *line)
{
	int		state;

	brk_find_symbol("add_history", (void **)&g_real_add_history);
	state = g_brk_hook_enable;
	g_brk_hook_enable = 0;
	g_real_add_history(line);
	g_brk_hook_enable = state;
}
