/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk_check_leaks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:55:40 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 02:52:00 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

__attribute__((destructor))
void	brk_check_leaks(void)
{
	t_alloc_list	*curr;
	t_alloc_list	*tmp;

	brk_log(DEBUG, "Checking for leaks...\n");
	curr = g_alloc_list;
	while (curr)
	{
		if (curr->ptr)
			brk_log(ERR, "Unfree'd pointer: %p\n", curr->ptr);
		tmp = curr;
		curr = curr->next;
		g_real_free(tmp);
	}
}
