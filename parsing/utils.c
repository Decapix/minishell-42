/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:50:11 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/17 08:42:58 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_intlen(int n)
{
	int	res;

	res = 1;
	while (n / 10)
	{
		res++;
		n = n / 10;
	}
	return (res);
}

int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isdollar(char c)
{
	if (ft_isalpha(c))
		return (1);
	else if (ft_isnum(c))
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

char	*mini_itoa(int n)
{
	if (!n)
		return ("0");
	if (n == 1)
		return ("1");
	if (n == 127)
		return ("127");
	return (0);
}
