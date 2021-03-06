/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nick.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/31 16:51:56 by marene            #+#    #+#             */
/*   Updated: 2016/03/21 17:48:11 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <server.h>

static int		is_empty(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (ft_iswhite(s[i]))
			return (1);
		++i;
	}
	return (0);
}

static char		*nick_msg(t_env *env, int cs, char *new_nick)
{
	char	*ret;
	char	*buff;

	ret = (env->fds[cs].nick == NULL) ? ft_itoa(cs) :
		ft_strdup(env->fds[cs].nick);
	buff = ft_strjoin(ret, " is now know as ");
	free(env->fds[cs].nick);
	env->fds[cs].nick = ft_strdup(new_nick);
	free(ret);
	ret = ft_strjoin(buff, new_nick);
	free(buff);
	return (ret);
}

static int		is_valid(t_env *env, int cs, char *nick)
{
	int		i;

	i = 0;
	if (is_empty(nick))
		return (0);
	while (i < env->max_fd)
	{
		if (i != cs && env->fds[i].type == FD_CLIENT
				&& ft_strequ(env->fds[i].nick, nick))
			return (0);
		++i;
	}
	return (1);
}

char			*handle_nick(t_env *env, int cs, char *input)
{
	char		*nick;
	char		*nick_m;
	size_t		nick_len;

	nick_len = ft_strlen("/NICK ");
	if (nick_len < ft_strlen(input))
	{
		nick = ft_strsub(input, nick_len, ft_strlen(input) - nick_len);
		free(input);
		input = NULL;
		if (is_valid(env, cs, nick))
		{
			nick_m = nick_msg(env, cs, nick);
			ringbuff_write(env->fds[cs].buf_write, nick_m, ft_strlen(nick_m));
			ringbuff_write(env->fds[cs].buf_write, "\n\r", 2);
			free(nick);
			return (nick_m);
		}
	}
	free(input);
	ringbuff_write(env->fds[cs].buf_write, "invalid nickname\n\r",
			RINGBUFF_CHUNK_SIZE);
	return (NULL);
}
