/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_left.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 13:19:34 by marene            #+#    #+#             */
/*   Updated: 2016/05/03 13:30:40 by marene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcurses.h"

char		handle_key_left(t_pane *p)
{
	if (p->cursor > 0)
		p->cursor -= 1;
	return ('\0');
}
