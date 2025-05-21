/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_special_buildin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 11:04:32 by apesic            #+#    #+#             */
/*   Updated: 2025/05/21 16:48:37 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	clean_garbage(t_leak *garbage)
{
	free_double_char(garbage->envp);
	free_double_char(garbage->arg);
	if (garbage->path)
		free_double_char(garbage->path);
	free(garbage->child_id);
	free(garbage);
	return (0);
}

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

t_leak	*nice_little_trash(t_env *mini_env, char **path, t_shell *command)
{
	t_leak	*garbage;

	garbage = ft_calloc(1, sizeof(t_leak));
	if (!garbage)
		exit_program(mini_env, 2);
	garbage->path = path;
	garbage->child_id = init_pid_array(mini_env, size_t_shell(command));
	return (garbage);
}

int	is_special_buildin(t_env *mini_env, t_shell *command, t_leak *garbage)
{
	if (!ft_strncmp(command->command->str, "exit", 5))
	{
		if (command->output == 3)
			return (0);
		else
			ft_exit(mini_env, garbage);
	}
	if (!ft_strncmp(command->command->str, "export", 7))
		ft_export(mini_env, command);
	if (!ft_strncmp(command->command->str, "unset", 6))
		ft_unset(mini_env, command);
	if (!ft_strncmp(command->command->str, "cd", 3))
		ft_cd(mini_env, command);
	return (0);
}
