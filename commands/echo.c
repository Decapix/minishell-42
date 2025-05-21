/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:55:31 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/21 18:45:13 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	check_for_n(char *str)
{
	if (!str)
		return (0);
	if (str[0] == '-' && str[1] == 'n' && !str[2])
		return (1);
	else
		return (0);
}

int	ft_echo(char **str)
{
	int	i;
	int	option;

	i = 1;
	option = check_for_n(str[1]);
	if (option)
		i++;
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		i++;
		if (str[i])
			write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}
