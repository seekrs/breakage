/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk_insert_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:34:21 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 02:59:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

t_alloc_list	*g_alloc_list = NULL;

void	brk_insert_alloc(void *ptr)
{
	t_alloc_list	*last;

	if (g_alloc_list == NULL)
	{
		g_alloc_list = g_real_malloc(sizeof(t_alloc_list));
		if (!g_alloc_list)
			brk_log(ERR, "internal malloc failed\n");
		if (!g_alloc_list)
			return ;
		g_alloc_list->ptr = ptr;
		g_alloc_list->next = NULL;
	}
	else
	{
		last = g_alloc_list;
		while (last->next)
			last = last->next;
		last->next = g_real_malloc(sizeof(t_alloc_list));
		if (!last->next)
			brk_log(ERR, "internal malloc failed\n");
		if (!last->next)
			return ;
		last->next->ptr = ptr;
		last->next->next = NULL;
	}
}
