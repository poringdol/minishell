/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 15:19:24 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/19 03:14:08 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		set_flag_p(t_list *node, unsigned flag)
{
	unsigned	**cont;

	cont = node->content;
	cont[0][0] = flag;
}

unsigned	get_flag_p(t_list *node)
{
	return (((unsigned **)(node->content))[0][0]);
}

char		*get_str(t_list *node)
{
	return (((char **)(node->content))[1]);
}
