/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 18:43:51 by fgavin            #+#    #+#             */
/*   Updated: 2020/10/01 18:40:22 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int			escape_delimiter(const char **next, const char *after_bs,
				t_list **list, size_t len)
{
	t_list		*node;
	int			delim;

	delim = is_delim(after_bs, "");
	if (delim == -1 || !(len % 2))
		return (1);
	node = create_node(after_bs - (len / 2), len, 0u, *list);
	if (push_node(list, node))
	{
		next = NULL;
		return (-1);
	}
	else
		*next = (delim == 4) ? after_bs + 2 : after_bs + 1;
	return (0);
}

const char	*got_backslash(const char *start, t_list **list, const char *params)
{
	t_list		*node;
	unsigned	flag;
	const char	*after_bs;
	size_t		len;
	const char	*next;

	after_bs = start;
	while (*after_bs == '\\')
		after_bs++;
	len = after_bs - start;
	if (!*params && !escape_delimiter(&next, after_bs, list, len))
		return (next);
	next = after_bs;
	if (*next && (*next == '$' || *next == '\"') && len % 2)
		next++;
	while (*next && *next != *params && is_delim(next, params) == -1)
		next++;
	if (*after_bs != '$' && *after_bs != '\"' && *params)
		len++;
	flag = (*next && *params && *next != *params) ? 1 : 0;
	len = len / 2;
	node = create_node(after_bs - len, next - (after_bs - len), flag, *list);
	if (push_node(list, node))
		return (NULL);
	return (next);
}

const char	*got_space(const char *start, t_list **list, const char *params)
{
	t_list		*node;
	unsigned	flag;

	while ((*start == ' ' || *start == '\t') && *start != *params)
		start++;
	flag = (*params && *params != *start) ? 1 : 0;
	flag |= !*params ? 32u : 0;
	node = create_node(" ", 1, flag, *list);
	if (push_node(list, node))
		return (NULL);
	return (start);
}

const char	*got_sing_quote(const char *start, t_list **list,
							const char *params)
{
	t_list		*node;
	const char	*next;
	unsigned	flag;

	start++;
	next = start;
	while (*next != '\'')
	{
		if (*next == *params)
			return (NULL);
		++next;
	}
	flag = (*(++next) && *params && *next != *params) ? 1 : 0;
	node = create_node(start, next - start - 1, flag, *list);
	if (push_node(list, node))
		return (NULL);
	return (next);
}

const char	*got_literal(const char *start, t_list **list, const char *params)
{
	char		*next;
	t_list		*node;
	unsigned	flag;

	flag = 0;
	next = (char *)start;
	while (*next != *params && is_delim(next, params) == -1)
	{
		if (!*next && *params)
			return (NULL);
		if (*next == '=' && !*params)
			flag = 16u;
		next++;
	}
	node = create_node(start, next - start, 0, *list);
	flag |= (*params && *next && *next != *params) ? 1u : 0;
	if (push_node(list, node))
		return (NULL);
	flag |= *list && !ft_strcmp(get_str(*list), "export") ? 4u : 0;
	set_flag_p(*list, get_flag_p(*list) | flag);
	next += *next == '\003' ? 1 : 0;
	return (next);
}
