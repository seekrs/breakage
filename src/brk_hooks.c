/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:14:47 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 06:19:49 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"
#define CHECK_LEAKS 0

int				g_brk_hook_enable = 1;

static void	brk_find_symbol(const char *name, void **ptr)
{
	if (*ptr == NULL)
	{
		brk_log(INFO, "finding %s...", name);
		*ptr = dlsym(RTLD_NEXT, name);
		if (!*ptr)
		{
			brk_fprintf(stderr, " failed\n");
			exit(1);
		}
		brk_fprintf(stderr, " %p\n", *ptr);
	}
}

void	add_history(const char *line)
{
	int		state;

	brk_find_symbol("add_history", (void **)&g_real_add_history);
	state = g_brk_hook_enable;
	g_brk_hook_enable = 0;
	g_real_add_history(line);
	g_brk_hook_enable = state;
}

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

void	*malloc(size_t size)
{
	void			*ptr;
	int				rval;

	brk_find_symbol("malloc", (void **)&g_real_malloc);
	if (g_brk_hook_enable == 0)
		return (g_real_malloc(size));
	if (size == 0)
		brk_log(WARN, "malloc called with size 0\n");
	if (g_brk_debug)
		brk_backtrace();
	brk_log(DEBUG, "malloc(%zu) = ", size);
	if (g_brk_fail_chance > 0)
	{
		rval = rand() % 100000;
		if (rval < g_brk_fail_chance && !g_brk_debug)
			brk_log(ERR, "malloc(%zu) = ", size);
		if (rval < g_brk_fail_chance)
		{
			brk_fprintf(stderr, "failed :^)\n");
			brk_backtrace();
			return (NULL);
		}
	}
	ptr = g_real_malloc(size);
	if (g_brk_debug)
		brk_fprintf(stderr, "%p\n", ptr);
	if (ptr == NULL)
		brk_log(ERR, "malloc failed (for real. whoops)\n");
	if (ptr == NULL || !CHECK_LEAKS)
		return (ptr);
	brk_insert_alloc(ptr);
	return (ptr);
}

void	free(void *ptr)
{
	t_alloc_list	*curr;

	brk_find_symbol("free", (void **)&g_real_free);
	if (g_brk_hook_enable == 0)
	{
		g_real_free(ptr);
		return ;
	}
	if (ptr == NULL)
		brk_log(WARN, "free called with NULL\n");
	else if (g_brk_hook_enable)
	{
		brk_log(DEBUG, "free(%p)\n", ptr);
		if (CHECK_LEAKS)
		{
			curr = g_alloc_list;
			while (curr && curr->ptr && curr->ptr != ptr)
				curr = curr->next;
			if (curr == NULL)
				brk_log(ERR, "free called with unknown pointer %p\n", ptr);
			else
				curr->ptr = NULL;
		}
	}
	g_real_free(ptr);
}
