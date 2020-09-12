/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgavin <fgavin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 02:50:10 by fgavin            #+#    #+#             */
/*   Updated: 2020/09/12 02:50:12 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static char	*find_env_var(char **var_list, char *str)
{
	int		i;

	i = 0;
	while (var_list[i])
	{
		if (!ft_strncmp(var_list[i], str, ft_strlen(str)) &&
			var_list[i][ft_strlen(str)] == '=')
			return (var_list[i]);
		i++;
	}
	return (NULL);
}

static char	*find_loc_var(t_list *var_list, char *str)
{
	char	**content;
	char	*tmp;
	char	*exp;

	while (var_list)
	{
		content = var_list->content;
		if (!ft_strcmp(content[0], str))
		{
			tmp = ft_strjoin(content[0], "=");
			exp = ft_strjoin(tmp, content[1]);
			free(tmp);
			return (exp);
		}
		var_list = var_list->next;
	}
	return (NULL);
}

int			ft_export(char **args)
{
	int		i;
	char	*exp;
	char	*tmp;

	exp = NULL;
	i = -1;
	while (args[++i])
	{
		exp = find_env_var(g_env_vars, args[i]);
		if (exp)
			continue;
		tmp = find_loc_var(g_loc_vars, args[i]);
		if (tmp)
			g_env_vars[ft_strlenbuf(g_env_vars)] = tmp;
	}
	return (0);
}
