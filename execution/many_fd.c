/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   many_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:40:58 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/14 11:57:43 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	close_and_zero(int fd)
{
	close(fd);
	return (0);
}

int	loop_for_input(t_env *mini_env, t_shell *command, int fd[4])
{
	t_io	*tmp;

	tmp = command->first_input;
	while (tmp)
	{
		if (fd[2])
			fd[2] = close_and_zero(fd[2]);
		if (set_input(mini_env, tmp, fd))
		{
			print_error(6);
			return (1);
		}
		tmp = tmp->next_io;
	}
	return (0);
}

void	loop_for_output(t_shell *command, int fd[4])
{
	t_io	*tmp;

	tmp = command->first_output;
	while (tmp)
	{
		if (fd[3])
			fd[3] = close_and_zero(fd[3]);
		set_output(tmp, fd);
		tmp = tmp->next_io;
	}
}

void	make_it_zero(int fd[4])
{
	fd[0] = 0;
	fd[1] = 0;
	fd[2] = 0;
	fd[3] = 0;
}

int	init_exec(t_env *mini_env, t_shell **command, int fd[4], char **path)
{
	int		status;

	status = 0;
	if (loop_for_input(mini_env, *command, fd))
		return (2);
	loop_for_output(*command, fd);
	if (!(*command)->command)
		return (2);
	if (!ft_isbuildin((*command)->command[0]))
		status = update_path(*command, path);
	else
		(*command)->is_buildin = 1;
	return (status);
}
