/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_client_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/31 16:04:38 by marene            #+#    #+#             */
/*   Updated: 2015/05/07 12:33:45 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <server.h>

extern t_cmd	g_cmd_table[CMD_NB];

static char		*handle_cmd(t_env *env, int cs, char *input)
{
	int		i;
	char	*tmp;
	char	*epur;
	char	sep;

	i = 0;
	epur = ft_epurstr(input);
	while (i < CMD_NB)
	{
		sep = input[ft_strlen(g_cmd_table[i].cmd)];
		if (ft_strstr(input, g_cmd_table[i].cmd) == input
				&& (ft_iswhite(sep) || sep == '\0'))
		{
			free(input);
			return (g_cmd_table[i].handler(env, cs, epur));
		}
		++i;
	}
	tmp = env->fds[cs].buf_write;
	env->fds[cs].buf_write = ft_strjoin(tmp, "\nCommand not found.");
	free(tmp);
	free(input);
	return (NULL);
}

char			*get_client_input(t_env *env, int cs, char *input)
{
	char	*trim;
	char	*epur;
	char	*buff;
	char	*ret;

	trim = ft_strtrim(input);
	epur = ft_epurstr(trim);
	if (trim[0] == CMD_CHAR)
		return (handle_cmd(env, cs, trim));
	else
	{
		ret = ft_strjoin(PUBLIC_OPEN, env->fds[cs].nick);
		buff = ret;
		ret = ft_strjoin(buff, PUBLIC_CLOSE);
		free(buff);
		buff = ret;
		ret = ft_strjoin(buff, epur);
		free(buff);
		free(trim);
		free(epur);
		return (ret);
	}
}
