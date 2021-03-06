/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_serv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/02 14:35:22 by marene            #+#    #+#             */
/*   Updated: 2016/05/05 14:56:25 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_error.h>
#include <client.h>

static int		is_exit(char *input)
{
	char	*trim;

	trim = ft_strtrim(input);
	if (trim && ft_strequ(trim, "/exit"))
	{
		free(trim);
		return (1);
	}
	else
	{
		free(trim);
		return (0);
	}
}

void			write_to_serv(t_env *env)
{
	int		ret;
	size_t	len;
	char	*buff;

	buff = NULL;
	len = ringbuff_read_to_str(env->buf_write, &buff, "\n\r");
	if (buff != NULL)
	{
		if (is_exit(buff))
			do_exit(env);
		ret = tryint(-1, send(env->s_sock, buff, len, 0), "send");
	}
}
