/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <sashe@bk.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 22:05:34 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/13 23:48:42 by pdemocri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include "minishell.h"

int			ft_echo(char **args)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (*args)
	{
		if (!ft_strcmp(args[0], "-n"))
		{
			flag = 1;
			i++;
		}
		while (args[i])
			ft_printf("%s", args[i++]);
	}
	if (!flag)
		ft_printf("\n");
	return (0);
}

/////////////////// сег фолт при попытке распечать несуществующую переменную
/////////////////// echo "text" | cat -e   -  лишние пробелы
