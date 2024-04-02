/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk_fprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 02:16:20 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 02:37:03 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

__attribute__((format(printf, 2, 3)))
void	brk_fprintf(FILE *stream, const char *format, ...)
{
	va_list	args;
	int		state;

	state = g_brk_hook_enable;
	g_brk_hook_enable = 0;
	va_start(args, format);
	vfprintf(stream, format, args);
	va_end(args);
	g_brk_hook_enable = state;
}
