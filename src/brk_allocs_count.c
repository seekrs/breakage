/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk_allocs_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 02:54:48 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 02:54:54 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

size_t	brk_allocs_count(void)
{
	t_alloc_list	*curr;
	size_t			count;

	count = 0;
	curr = g_alloc_list;
	while (curr)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}
