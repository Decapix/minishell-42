/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:57:50 by apesic            #+#    #+#             */
/*   Updated: 2025/05/17 06:18:42 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_isbuildin(char *str)
	//check for last item if it is \n if this function does work
{
	if (!ft_strncmp(str, "echo", 5))
		return (1);
	if (!ft_strncmp(str, "cd", 3))
		return (1);
	if (!ft_strncmp(str, "pwd", 4))
		return (1);
	if (!ft_strncmp(str, "export", 7))
		return (1);
	if (!ft_strncmp(str, "unset", 6))
		return (1);
	if (!ft_strncmp(str, "env", 4))
		return (1);
	if (!ft_strncmp(str, "exit", 5))
		return (1);
	return (0);
}

int	error_child(t_env *mini_env, t_list *lst, char **arg, char **envp)
{
	ft_putstr_fd("minishell: no such file or directory: ", 2);
	ft_putstr_fd(lst->str, 2);
	ft_putstr_fd("\n", 2);
	free_double_char(envp);
	free_double_char(arg);
	exit_program(mini_env, 127);
	return (127);
}

int	size_t_shell(t_shell *command)
{
	int	res;

	res = 0;
	while (command)
	{
		if (command->command)
			res++;
		command = command->next_command;
	}
	return (res);
}

pid_t	*init_pid_array(t_env *mini_env, int nb_of_command)
{
	pid_t	*res;

	res = ft_calloc(nb_of_command, sizeof(pid_t));
	if (!res)
		exit_program(mini_env, 2);
	return (res);
}

void	paint_in_red(pid_t *child_id, int total_child)
{
	int	i;

	i = 0;
	while (i < total_child)
		if (child_id[i++])
			kill(child_id[i - 1], SIGKILL);
}
