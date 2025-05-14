/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:55:31 by jlepany           #+#    #+#             */
/*   Updated: 2025/04/08 12:00:24 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	check_for_n(char *str)
{
	if (str[0] == '-' && str[1] == 'n' && !str[2])
		return (1);
	else
		return (0);
}

int	echo(char **str)
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
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}
