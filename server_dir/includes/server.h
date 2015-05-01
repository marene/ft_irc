/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/29 11:40:49 by marene            #+#    #+#             */
/*   Updated: 2015/05/01 10:55:51 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/select.h>
# include <netinet/in.h>

# define FD_FREE		0
# define FD_SERV		1
# define FD_CLIENT		2
# define SERV_ERROR		-1
# define SERV_OK		0
# define SERV_USAGE		": <port>"
# define QUEUE_SIZE		42
# define BUF_SIZE		1024
# define CMD_CHAR		'/'
# define CMD_NB			4
# define DEFAULT_CHAN	0
# define CMD_ERROR		"Sorry, command not found :/"

typedef struct				s_fd
{
	int		type;
	int		chan;
	void	(*fct_read)();
	void	(*fct_write)();
	char	buf_read[BUF_SIZE + 1];
	char	*buf_write;
	char	*nick;
}							t_fd;

typedef struct				s_channel
{
	int					id;
	char				*name;
	struct s_channel	*next;
}							t_channel;

typedef struct				s_env
{
	t_fd		*fds;
	t_channel	*chans;
	int			port;
	int			max_fd;
	int			max;
	int			r;
	fd_set		fd_read;
	fd_set		fd_write;
}							t_env;

typedef struct				s_cmd
{
	char	cmd[11];
	char	*(*handler)();
}							t_cmd;

typedef struct sockaddr		t_sockaddr;

void						init_env(t_env *env);
void						clean_fd(t_fd *fd);
void						get_opt(t_env *env, int argc, char **argv);
void						srv_create(t_env *env);
void						run_srv(t_env *env);
void						disp_new_client(int c_sock, struct sockaddr_in c);
void						disp_client_away(t_env *env, int cs);
void						init_fd(t_env *env);
void						check_fd(t_env *env);
void						client_read(t_env *env, int cs);
void						client_write(t_env *env, int cs);
void						srv_accept(t_env *env, int s);
char						*get_client_input(t_env *env, int cs, char *input);
t_channel					*create_channel(int id, char *name);
int							add_channel(t_env *env, t_channel *new);
char						*get_chan_by_id(t_channel *chan, int id);

/*
** command handlers
*/

char						*handle_nick(t_env *env, int cs, char *input);
char						*handle_join(t_env *env, int cs, char *input);
char						*handle_who(t_env *env, int cs, char *input);
char						*handle_msg(t_env *env, int cs, char *input);
#endif
