/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:02:29 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/19 17:44:53 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../libft/libft.h"

void	read_with_here_doc(t_env *mini_env, char *here_eof, int fd[4])
{
	char	*buff;
	int		len;

	close(fd[2]);
	ft_putstr_fd("> ", 1);
	buff = get_next_line(0);
	len = ft_strlen(here_eof);
	here_eof[len] = '\n';
	while (ft_strncmp(buff, here_eof, len + 1))
	{
		ft_putstr_fd(buff, fd[3]);
		free(buff);
		ft_putstr_fd("> ", 1);
		buff = get_next_line(0);
	}
	here_eof[len] = 0;
	free(buff);
	close(fd[3]);
	exit_program(mini_env, -1);
}

int	here_doc_parent(pid_t child_id, int fd[4])
{
	close(fd[3]);
	while (!(waitpid(child_id, 0, WNOHANG)))
		if (g_status == 2)
			kill(child_id, SIGKILL);
	return (0);
}

int	set_input(t_env *mini_env, t_io	*input, int fd[4])
{
	pid_t	child_id;

	if (input->io_mode == 1)
	{
		if (access(input->io_name, F_OK | R_OK))
			return (1);
		fd[2] = open(input->io_name, O_RDONLY, 0666);
	}
	if (input->io_mode == 2)
	{
		pipe(&fd[2]);
		child_id = fork();
		if (!child_id)
			read_with_here_doc(mini_env, input->io_name, fd);
		if (here_doc_parent(child_id, fd))
			return (1);
	}
	if (input->io_mode == 3)
	{
		fd[2] = dup(fd[0]);
		if (fd[2] == -1)
			perror("mince mince...");
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
		if (fd[3])
			fd[3] = close_and_zero(fd[3]);
		fd[3] = dup(fd[1]);
		close(fd[1]);
	}
}

void	execute_command(t_env *mini_env, t_shell *command, char **path)
{
	int		fd[4];
	int		i;
	int		status;
	pid_t	*child_id;

	child_id = init_pid_array(mini_env, size_t_shell(command));
	i = 0;
	make_it_zero(fd);
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
	mini_env->exit = sig_ctr(child_id, size_t_shell(mini_env->first_command));
	free(child_id);
}
