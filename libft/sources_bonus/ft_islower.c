/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdemocri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:42:10 by pdemocri          #+#    #+#             */
/*   Updated: 2020/09/15 21:05:13 by fgavin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_islower(int ch)
{
	if (ch >= 'a' && ch <= 'z')
		return (ch);
	return (0);
}
