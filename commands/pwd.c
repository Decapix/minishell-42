/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:58:30 by apesic            #+#    #+#             */
/*   Updated: 2025/05/13 17:25:48 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		free(cwd);
	}
	else
		return (1);
	return (0);
}
