/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk_log.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:23:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 02:33:06 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

void	brk_log(const char *level, const char *msg, ...)
{
	va_list	args;
	int		state;

	if (level && !strcmp(DEBUG, level) && !g_brk_debug)
		return ;
	state = g_brk_hook_enable;
	g_brk_hook_enable = 0;
	brk_fprintf(stderr, "%s ", level);
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);
	g_brk_hook_enable = state;
}
