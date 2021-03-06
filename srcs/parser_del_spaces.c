/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_del_spaces.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:04:42 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/19 03:12:41 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	set_flag(t_list *prev, t_list *curr)
{
	int				flag;

	flag = 0;
	if ((!prev || is_redirect(get_str(prev), get_flag_p(prev))) &&
		!ft_strcmp(get_str(curr), "echo"))
		flag = 1;
	if (curr->content && is_redirect(get_str(curr), get_flag_p(curr)))
		flag = 0;
	return (flag);
}

void		del_lead_spaces(t_list **list)
{
	t_list		*tmp;

	while (*list && !(ft_strcmp(get_str(*list), " ")))
	{
		tmp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = tmp;
	}
}

void		ft_delspace(t_list **list)
{
	int			flag;
	t_list		*prev;
	t_list		*curr;

	prev = NULL;
	del_lead_spaces(list);
	curr = *list;
	while (curr)
	{
		flag = set_flag(prev, curr);
		if ((!flag ||
			(prev && !ft_strcmp(get_str(prev), "echo"))) &&
				!ft_strcmp(get_str(curr), " ") &&
			(prev && !(get_flag_p(prev) & 1)))
		{
			prev->next = curr->next;
			ft_lstdelone(curr, free);
			curr = prev->next;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void		del_redirect_spaces(t_list **list)
{
	t_list		*tmp;
	t_list		*start;

	start = *list;
	while (*list)
	{
		if (is_redirect(get_str(*list), get_flag_p(*list)) &&
			(*list)->next && !ft_strcmp(get_str((*list)->next), " ") &&
			(get_flag_p((*list)->next) & 32))
		{
			tmp = (*list)->next->next;
			free((*list)->next->content);
			free((*list)->next);
			(*list)->next = tmp;
		}
		else
			*list = (*list)->next;
	}
	*list = start;
}
