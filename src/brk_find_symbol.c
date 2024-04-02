/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk_find_symbol.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 07:13:45 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 07:13:56 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

void	brk_find_symbol(const char *name, void **ptr)
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
