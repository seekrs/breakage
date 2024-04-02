/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:11:49 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 06:29:45 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file break.h
 * @author kiroussa
 * @version 0.1
 *
 * @brief A reimplementation of the malloc function that randomly breaks =)
 */

#ifndef BRK_H
# define BRK_H

# define _GNU_SOURCE // useful for RTLD_NEXT
# include <dlfcn.h>
# undef _GNU_SOURCE
# include <execinfo.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

# define INFO		"\033[1;32mINFO\033[0m"
# define WARN		"\033[1;33mWARN\033[0m"
# define ERR		"\033[1;31m ERR\033[0m"
# define DEBUG		"\033[1;34m DBG\033[0m"

extern int			g_brk_hook_enable;
extern int			g_brk_debug;
extern int			g_brk_fail_chance;
extern int			g_brk_log_enable;

extern void			*(*g_real_malloc)(size_t size);
extern void			(*g_real_free)(void *ptr);
extern char			*(*g_real_readline)(const char *prompt);
extern void			(*g_real_add_history)(const char *string);

typedef struct s_alloc_list
{
	void				*ptr;
	struct s_alloc_list	*next;
}	t_alloc_list;

extern t_alloc_list	*g_alloc_list;

size_t	brk_allocs_count(void);
void	brk_log(const char *level, const char *msg, ...)
					__attribute__((format(printf, 2, 3)));
void	brk_fprintf(FILE *stream, const char *msg, ...)
					__attribute__((format(printf, 2, 3)));
void	brk_insert_alloc(void *ptr);
void	brk_backtrace(void);

void	*malloc(size_t size);
void	free(void *ptr);

#endif // BRK_H
