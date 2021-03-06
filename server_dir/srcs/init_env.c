/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/29 11:59:34 by marene            #+#    #+#             */
/*   Updated: 2014/10/31 13:35:18 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/resource.h>
#include <server.h>
#include <ft_error.h>

void	init_env(t_env *env)
{
	int				i;
	struct rlimit	r_info;

	i = 0;
	tryint(-1, getrlimit(RLIMIT_NOFILE, &r_info), "getrlimit failed");
	env->max_fd = r_info.rlim_cur;
	env->fds = tryptr(0, malloc(sizeof(*env->fds) * env->max_fd), "malloc");
	env->chans = create_channel(DEFAULT_CHAN, "default");
	while (i < env->max_fd)
	{
		clean_fd(&env->fds[i]);
		++i;
	}
}
