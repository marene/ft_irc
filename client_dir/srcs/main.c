/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/10/22 19:05:16 by marene            #+#    #+#             */
/*   Updated: 2015/04/28 11:38:39 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <libft.h>
#include <client.h>
#include <ft_error.h>

int		main(int argc, char **argv)
{
	t_env		env;

	init_env(&env);
	get_opt(&env, argc, argv);
	create_client(&env);
	run_client(&env);
	return (EXIT_SUCCESS);
}
