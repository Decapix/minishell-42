/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_buildin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:04:32 by apesic            #+#    #+#             */
/*   Updated: 2025/05/17 06:36:43 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	decrement_return_z(int *to_decrement)
{
	(*to_decrement)--;
	return (0);
}

int	sync_status(int status)
{
	WEXITSTATUS(status);
	if (status == 256)
		status = 1;
	if (status == 32512)
		status = 127;
	if (g_status == 2)
		status = 130;
	return (status);
}

int	is_special_buildin(t_env *mini_env, t_shell *command)
	//execute export, unset and exit. exit is ignore if it is inside a pipe
{
	if (!ft_strncmp(command->command->str, "exit", 5))
	{
		if (command->output == 3)
			return (0);
		else
			ft_exit(mini_env, 0);
	}
	if (!ft_strncmp(command->command->str, "export", 7))
	{
		if (!command->command->next)
			ft_env(mini_env);
		else
			ft_export(mini_env, command);
	}
	if (!ft_strncmp(command->command->str, "unset", 6))
		ft_unset(mini_env, command);
	return (0);
}
