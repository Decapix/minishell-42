/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_buildin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:04:32 by apesic            #+#    #+#             */
/*   Updated: 2025/05/16 15:18:40 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
	if (!ft_strncmp(command->command->str, "cd", 3))
		ft_cd(mini_env, command);
	return (0);
}
