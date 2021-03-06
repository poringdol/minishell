/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:03:14 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/19 03:00:27 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "redirect.h"

int			redirect_2(t_list *parse)
{
	while (parse && !is_redirect(get_str(parse), get_flag_p(parse)))
		parse = parse->next;
	parse = parse ? parse->next : parse;
	if ((!parse || !get_str(parse)) ||
			is_redirect(get_str(parse), get_flag_p(parse)))
		return (print_error("minishell: syntax error", 2));
	if (pipe(g_pipe) == -1)
		return (errno);
	return (0);
}

static char	*get_filename(t_list *parse)
{
	char		*res;

	res = NULL;
	while (parse && !(is_redirect(get_str(parse), get_flag_p(parse))))
		parse = parse->next;
	if (parse->next &&
			!(is_redirect(get_str(parse->next), get_flag_p(parse->next))))
		res = get_str(parse->next);
	return (res);
}

int			redirect_3(t_list *parse)
{
	const char	*filename = get_filename(parse);

	if (!filename)
	{
		if (!is_redirect(get_str(parse), get_flag_p(parse)))
			return (print_error("minishell: syntax error", 2));
		else
			return (2);
	}
	close(1);
	g_pipe[1] = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (g_pipe[1] < 0)
	{
		open_stdin_stdout();
		return (print_error(strerror(errno), 1));
	}
	return (0);
}

int			redirect_4(t_list *parse)
{
	const char	*filename = get_filename(parse);

	if (!filename)
	{
		if (!is_redirect(get_str(parse), get_flag_p(parse)))
			return (print_error("minishell: syntax error", 2));
		else
			return (2);
	}
	close(1);
	g_pipe[1] = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (g_pipe[1] < 0)
	{
		open_stdin_stdout();
		return (print_error(strerror(errno), 1));
	}
	return (0);
}

int			redirect_5(t_list *parse)
{
	const char	*filename = get_filename(parse);

	if (!filename)
	{
		if (!is_redirect(get_str(parse), get_flag_p(parse)))
			return (print_error("minishell: syntax error", 2));
		else
			return (2);
	}
	close(0);
	g_pipe[0] = open(filename, O_RDONLY);
	if (g_pipe[0] < 0)
	{
		open_stdin_stdout();
		return (print_error(strerror(errno), 1));
	}
	return (0);
}
