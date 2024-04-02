/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brk_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 01:36:53 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/02 02:57:47 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brk.h"

int		g_brk_fail_chance = 0;
int		g_brk_debug = 0;

static void	brk_parse_env(void)
{
	int		i;
	char	*env;

	i = 0;
	while (__environ[i])
	{
		env = __environ[i];
		if (!strncmp(env, "BRK_FAIL_CHANCE=", 16))
		{
			g_brk_fail_chance = atoi(__environ[i] + 16);
			brk_log(INFO, "malloc fail chance "
				"set to %d%%\n", g_brk_fail_chance);
		}
		if (!strncmp(env, "BRK_DEBUG", 9))
		{
			g_brk_debug = 1;
			brk_log(DEBUG, "enable debug logging\n");
		}
		i++;
	}
}

void	*(*g_real_malloc)(size_t size);
void	(*g_real_free)(void *ptr);
char	*(*g_real_readline)(const char *prompt);

__attribute__((constructor))
void	brk_init(void)
{
	srand(time(NULL));
	brk_parse_env();
	brk_log(INFO, "brk initialized, scanning for dumb shit\n");
}
