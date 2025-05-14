/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:02:29 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/14 07:13:04 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../libft/libft.h"

void	read_with_here_doc(t_env *mini_env, char *here_eof, int fd[4])
{
	char	*buff;

	close(fd[0]);
	ft_putstr_fd("here_doc> ", 1);
	buff = get_next_line(0);
	while (ft_strncmp(buff, here_eof, ft_strlen(buff) - 1))
	{
		ft_putstr_fd(buff, fd[1]);
		free(buff);
		ft_putstr_fd("here_doc> ", 1);
		buff = get_next_line(0);
	}
	free(buff);
	close(fd[1]);
	exit_program(mini_env, -1);
}

int	set_input(t_env *mini_env, t_io	*input, int fd[4])
{
	if (input->io_mode == 1)
	{
		if (access(input->io_name, F_OK | R_OK))
			return (1);
		fd[2] = open(input->io_name,  O_RDONLY, 0666);
	}
	if (input->io_mode == 2)
	{
		pipe(fd);
		if (!fork())
			read_with_here_doc(mini_env, input->io_name, fd);
		wait(0);
		close(fd[1]);
		dup2(fd[0], fd[2]);
		close(fd[0]);
	}
	if (input->io_mode == 3)
	{
		fd[2] = dup(fd[0]);
		close(fd[0]);
	}
	return (0);
}

void	set_output(t_io *output, int fd[4])
{
	if (output->io_mode == 1)
	{
		if (access(output->io_name, F_OK | W_OK))
			fd[3] = open(output->io_name, O_RDWR | O_CREAT, 0666);
		else
			fd[3] = open(output->io_name, O_WRONLY | O_TRUNC, 0666);
	}
	if (output->io_mode == 2)
	{
		if (access(output->io_name, F_OK | W_OK))
			fd[3] = open(output->io_name, O_RDWR | O_CREAT, 0666);
		else
			fd[3] = open(output->io_name, O_WRONLY | O_APPEND, 0666);
	}
	if (output->io_mode == 3)
	{
		pipe(&fd[0]);
		fd[3] = dup(fd[1]);
		close(fd[1]);
	}
}

int	init_exec(t_env *mini_env, t_shell **command, int fd[4], char **path)
{
	int		status;
	t_io	*tmp;

	status = 0;
	tmp = (*command)->first_input;
	while (tmp)
	{
		if (set_input(mini_env, tmp, fd))
		{
			print_error(6);
			return (2);
		}
		tmp = tmp->next_io;
	}
	tmp = (*command)->first_output;
	while (tmp)
	{
		set_output(tmp, fd);
		tmp = tmp->next_io;
	}
	if (!(*command)->command)
		return (2);
	if (!ft_isbuildin((*command)->command[0]))
		status = update_path(*command, path);
	else
		(*command)->is_buildin = 1;
	return (status);
}

void	execute_command(t_env *mini_env, t_shell *command, char **path)
{
	int		fd[4];
	int		i;
	int		status;
	pid_t	*child_id;

	child_id = init_pid_array(mini_env, size_t_shell(command));
	i = 0;
	while (command)
	{
		status = init_exec(mini_env, &command, fd, path);
		if (status == 2)
			break ;
		if (status == -1)
			exit_program(mini_env, 2);
		child_id[i++] = exec_com(mini_env, command, fd);
		is_special_buildin(mini_env, command);
		command = command->next_command;
	}
	control_for_signal(child_id, size_t_shell(mini_env->first_command));
	free(child_id);
	printf("all command over\n");
}
