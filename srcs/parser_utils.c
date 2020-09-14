/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 18:36:47 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/15 00:58:28 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list			*create_node(const char *data, size_t len, unsigned flag)
{
	t_list		*node;
	char		**n_data;
	unsigned	*flg;

	if (!((n_data = ft_calloc(1, ++len * sizeof(char) +
		sizeof(void *) * 2 + sizeof(unsigned))) &&
		(node = ft_lstnew(NULL))))
	{
		free(n_data);
		free(node);
		return (NULL);
	}
	n_data[0] = (char *)n_data + sizeof(void *) * 2;
	n_data[1] = (char *)n_data + sizeof(void *) * 2 + sizeof(unsigned);
	flg = (unsigned *)n_data[0];
	*flg = flag;
	ft_strlcpy(n_data[1], data, len);
	node->content = n_data;
	return (node);
}

int				push_node(t_list **list, t_list *new_node)
{
	if (!new_node)
		return (1);
	if (!*list)
		*list = new_node;
	else
		ft_lstadd_front(list, new_node);
	return (0);
}

int				is_delim(const char *str, const char *eot)
{
	int			i;
	const char	*ptr;

	i = -1;
	while (++i < DELIM_NUM)
	{
		ptr = str;
		if (!ft_strncmp(ptr, g_delims[i].data, (i == 4) ? 2 : 1))
			break ;
	}
	if (i == DELIM_NUM)
		return (-1);
	if (!*eot)
		return (i);
	if (!g_delims[i].ign_q)
		return (-1);
	return (i);
}

char			*get_var(const char *str)
{
	if (ft_isdigit(*str))
	{
		while (*str && ft_isdigit(*str))
			str++;
	}
	else if (ft_strchr("?", *str))
		str++;
	else
	{
		while (*str && (*str == '_' || ft_isalnum(*str)))
			str++;
	}
	return ((char *)str);
}
