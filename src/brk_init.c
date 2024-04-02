/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:36:53 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 07:55:25 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

int		g_brk_fail_chance = 0;
int		g_brk_debug = 0;
int		g_brk_log_enable = 1;
int		g_brk_hook_enable = 1;

/**
 * @note Yes I know it's shit, I don't care.
 */
static void	brk_parse_env(void)
{
	int		i;
	float	tmp;

	i = 0;
	while (__environ[i])
	{
		if (!strncmp(__environ[i], "BRK_FAIL_CHANCE=", 16))
		{
			g_brk_fail_chance = atoi(__environ[i] + 16);
			tmp = ((float)g_brk_fail_chance) / 100.;
			brk_log(INFO, "malloc fail chance "
				"set to %f%%\n", tmp);
		}
		if (!strncmp(__environ[i], "BRK_DEBUG", 9))
		{
			g_brk_debug = 1;
			brk_log(DEBUG, "enable debug logging\n");
		}
		if (!strncmp(__environ[i], "BRK_NO_LOG", 10))
		{
			g_brk_log_enable = 0;
			brk_log(DEBUG, "disable logging\n");
		}
		i++;
	}
}

void	*(*g_real_malloc)(size_t size);
void	(*g_real_free)(void *ptr);
char	*(*g_real_readline)(const char *prompt);
void	(*g_real_add_history)(const char *line);

__attribute__((constructor))
void	brk_init(void)
{
	srand(time(NULL));
	brk_parse_env();
	brk_log(INFO, "brk initialized in %d\n", getpid());
}
