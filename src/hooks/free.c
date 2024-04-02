/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 07:19:41 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 07:20:17 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

void	free(void *ptr)
{
	t_alloc_list	*curr;

	brk_find_symbol("free", (void **)&g_real_free);
	if (g_brk_hook_enable)
	{
		if (ptr == NULL)
			brk_log(WARN, "free called with NULL\n");
		else
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
	}
	g_real_free(ptr);
}
