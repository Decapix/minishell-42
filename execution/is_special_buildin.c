/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_buildin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:04:32 by apesic            #+#    #+#             */
/*   Updated: 2025/05/13 17:41:51 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_special_buildin(t_env *mini_env, t_shell *command)
	//execute export, unset and exit. exit is ignore if it is inside a pipe
{
	if (!ft_strncmp(command->command[0], "exit", 5))
	{
		if (command->output == 3)
			return (0);
		else
			ft_exit(mini_env, 0);
	}
	if (!ft_strncmp(command->command[0], "export", 7))
	{
		if (!command->command[1])
			ft_env(t_env_to_arr(mini_env));
		else
			ft_export(mini_env, command);
	}
	if (!ft_strncmp(command->command[0], "unset", 6))
		ft_unset(mini_env, command);
	return (0);
}
