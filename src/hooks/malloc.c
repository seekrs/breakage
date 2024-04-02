/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 07:15:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 07:35:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

static int	brk_malloc_should_fail(size_t size)
{
	int	rval;

	if (g_brk_fail_chance > 0)
	{
		rval = rand() % 10000;
		if (rval < g_brk_fail_chance)
		{
			if (!g_brk_debug)
				brk_log(ERR, "malloc(%zu) = ", size);
			brk_fprintf(stderr, "failed :^)\n");
			if (g_brk_debug)
				brk_backtrace();
			return (1);
		}
	}
	return (0);
}

void	*malloc(size_t size)
{
	void			*ptr;

	brk_find_symbol("malloc", (void **)&g_real_malloc);
	if (g_brk_hook_enable == 0)
		return (g_real_malloc(size));
	if (size == 0)
		brk_log(WARN, "malloc called with size 0\n");
	brk_log(DEBUG, "malloc(%zu) = ", size);
	if (g_brk_fail_chance > 0 && brk_malloc_should_fail(size))
		return (NULL);
	ptr = g_real_malloc(size);
	if (g_brk_debug)
	{
		brk_fprintf(stderr, "%p\n", ptr);
		brk_backtrace();
	}
	if (ptr == NULL)
		brk_log(ERR, "malloc failed (for real. womp womp)\n");
	else if (CHECK_LEAKS)
		brk_insert_alloc(ptr);
	return (ptr);
}
