/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 01:33:56 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/17 03:35:04 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int		is_func(char *str)
{
	const char	*funcs_str[8] = {NULL,
								"echo",
								"cd",
								"pwd",
								"export",
								"unset",
								"env",
								"exit"};
	int			i;

	i = 0;
	if (!str)
		return (0);
	while (++i < 8)
		if (!ft_strcmp(funcs_str[i], str))
			return (i);
	return (0);
}

int		is_redirect(char *str)
{
	int			i;
	const char	redir[6][3] = {"", ";", "|", ">", ">>", "<"};

	i = 0;
	while (++i < 6)
	{
		if (!ft_strcmp(str, redir[i]))
			return (i);
	}
	return (0);
}

int		next_redirect(t_list *parse)
{
	int		i;

	i = 0;
	while (parse && !(i = is_redirect(get_str(parse))))
		parse = parse->next;
	return (i);
}

int		check_redirect(t_list **parse)
{
	int				ret;
	const int		pipe_status = next_redirect(*parse);

	if (pipe_status > 1)
		ret = g_funcs_red[pipe_status](*parse);
	if (pipe_status >= 3)
	{
		while (*parse && !is_redirect(get_str(*parse)))
			*parse = (*parse)->next;
		*parse = (*parse)->next;
	}
	if (!pipe_status)
		ret = open_stdin_stdout();
	g_exit_status = ret ? ret : g_exit_status;
	g_pipe_next = pipe_status;
	return (ret);
}
