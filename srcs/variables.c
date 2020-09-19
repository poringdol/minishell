/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 17:57:46 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/19 03:12:52 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list		*find_elem(t_list *list, char *key)
{
	while (list)
	{
		if (!ft_strcmp(key, ((char **)list->content)[0]))
			return (list);
		list = list->next;
	}
	return (NULL);
}

int			add_var_to_list(t_list **list, char **cont, int create)
{
	t_list		*tmp_node;
	char		**tmp_cont;

	if ((tmp_node = find_elem(*list, cont[0])))
	{
		free(((char **)(tmp_node->content))[1]);
		if (!(((char **)(tmp_node->content))[1] = ft_strdup(cont[1])))
			return (1);
	}
	else if (create)
	{
		if (!(tmp_cont = ft_calloc(2, sizeof(void*))))
			return (1);
		if (!(tmp_cont[0] = ft_strdup(cont[0])) ||
			!(tmp_cont[1] = ft_strdup(cont[1])))
		{
			del_var_cont(tmp_cont);
			return (1);
		}
		if (!*list)
			*list = ft_lstnew(tmp_cont);
		else
			ft_lstadd_front(list, ft_lstnew(tmp_cont));
	}
	return (0);
}

int			check_var_in_env(char **var_list, char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (var_list[i])
	{
		if (!ft_strncmp(var_list[i], str[0], ft_strlen(str[0])) &&
			var_list[i][ft_strlen(str[0])] == '=')
		{
			tmp = ft_strjoin(str[0], "=");
			var_list[i] = ft_strjoin(tmp, str[1]);
			free(tmp);
			return (0);
		}
		i++;
	}
	return (0);
}

int			add_var_to_env(char **cont)
{
	int			i;
	int			idx;
	char		*tmp;

	i = -1;
	if ((idx = find_env_var(g_env_vars, cont[0])) != -1)
		free(g_env_vars[idx]);
	else
	{
		while (++i < ENV_LENGTH && g_env_vars[i])
			;
		if (i == ENV_LENGTH)
			return (1);
		idx = i;
	}
	tmp = ft_strjoin("=", cont[1]);
	if (!(g_env_vars[idx] = ft_strjoin(cont[0], tmp)))
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

char		*got_var(const char *start, const char *eq_sign, const char *params,
	t_list *head)
{
	const char	*end;
	char		*cont[2];
	int			err_flg;

	err_flg = 0;
	end = eq_sign;
	while (*end && is_delim(end, params) < 0)
		end++;
	if (cr_var_cont(start, eq_sign, end - 1, (char **)cont))
		return (NULL);
	if (head && (get_flag_parser(head) & 4u) != 0)
	{
		err_flg = add_var_to_env(cont) ? 1 : 0;
		while (head && ft_strcmp(get_str(head), "export"))
			head = head->next;
		if (head)
			set_flag_parser(head, get_flag_parser(head) | 8u);
	}
	else
		check_var_in_env(g_env_vars, cont);
	if (!err_flg && add_var_to_list(&g_loc_vars, cont, 1))
		err_flg = 1;
	return (err_flg + free_str(&cont[0]) +
		free_str(&cont[1]) ? NULL : (char *)end);
}
