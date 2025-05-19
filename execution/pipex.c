/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:02:29 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/17 06:20:44 by jlepany          ###   ########.fr       */
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

// The pipe file descriptor array used between commands
static int	g_pipe_fds[2] = {-1, -1};
static int	g_prev_pipe_read = -1;

// Sets up input redirection for a command
int	set_input(t_env *mini_env, t_io	*input, int fd[4])
{
	pid_t	child_id;

	// File input
	if (input->io_mode == 1)
	{
		if (access(input->io_name, F_OK | R_OK))
			return (1);  // File doesn't exist or can't be read
		fd[2] = open(input->io_name, O_RDONLY, 0666);
	}
	// Here document
	else if (input->io_mode == 2)
	{
		int pipe_fds[2];

		if (pipe(pipe_fds) == -1)
		{
			perror("pipe error");
			return (1);
		}

		fd[2] = pipe_fds[0];  // Read end
		fd[3] = pipe_fds[1];  // Write end

		child_id = fork();
		if (!child_id)
			read_with_here_doc(mini_env, input->io_name, fd);
		if (here_doc_parent(child_id, fd))
			return (1);
	}
	// Pipe input from previous command
	else if (input->io_mode == 3)
	{
		// Use the previous pipe's read end
		if (g_prev_pipe_read != -1)
		{
			fd[2] = g_prev_pipe_read;
		}
		else
		{
			write(2, "Error: No pipe input available\n", 31);
			return (1);
		}
	}
	return (0);
}

// Sets up output redirection for a command
void	set_output(t_io *output, int fd[4])
{
	// Regular file output (truncate)
	if (output->io_mode == 1)
	{
		if (access(output->io_name, F_OK | W_OK))
			fd[3] = open(output->io_name, O_RDWR | O_CREAT, 0666);
		else
			fd[3] = open(output->io_name, O_WRONLY | O_TRUNC, 0666);
	}
	// Append to file
	else if (output->io_mode == 2)
	{
		if (access(output->io_name, F_OK | W_OK))
			fd[3] = open(output->io_name, O_RDWR | O_CREAT, 0666);
		else
			fd[3] = open(output->io_name, O_WRONLY | O_APPEND, 0666);
	}
	// Pipe output to next command
	else if (output->io_mode == 3)
	{
		// Create a new pipe for the next command
		if (pipe(g_pipe_fds) == -1)
		{
			perror("pipe error");
			return;
		}

		// Use write end for output
		fd[3] = g_pipe_fds[1];

		write(2, "Created pipe for next command: read=", 36);
		char num[10];
		snprintf(num, sizeof(num), "%d", g_pipe_fds[0]);
		write(2, num, ft_strlen(num));
		write(2, " write=", 7);
		snprintf(num, sizeof(num), "%d", g_pipe_fds[1]);
		write(2, num, ft_strlen(num));
		write(2, "\n", 1);
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

	// Initialize global pipe state
	g_prev_pipe_read = -1;
	g_pipe_fds[0] = -1;
	g_pipe_fds[1] = -1;

	while (command)
	{
		// Reset fd array for each command
		make_it_zero(fd);

		// Set up redirections and prepare command
		status = init_exec(mini_env, &command, fd, path);
		if (status == 2)
			break;
		if (status == -1)
			exit_program(mini_env, 2);

		// Execute command with redirections
		child_id[i++] = exec_com(mini_env, command, fd);

		// Handle special builtins
		is_special_buildin(mini_env, command);

		// After command is started, save the read end of the pipe for the next command
		if (g_pipe_fds[0] != -1)
		{
			// Close previous pipe read end if exists
			if (g_prev_pipe_read != -1)
				close(g_prev_pipe_read);

			// Save the new pipe read end for the next command
			g_prev_pipe_read = g_pipe_fds[0];

			// Write end is already passed to the command, so clear it
			g_pipe_fds[0] = -1;
			g_pipe_fds[1] = -1;
		}

		// Move to next command
		command = command->next_command;
	}

	// Close any remaining pipes
	if (g_prev_pipe_read != -1)
		close(g_prev_pipe_read);
	if (g_pipe_fds[0] != -1)
		close(g_pipe_fds[0]);
	if (g_pipe_fds[1] != -1)
		close(g_pipe_fds[1]);

	// Make sure all other fds are closed in the parent process
	close_remaining_fds(fd);

	// Wait for all child processes to complete
	mini_env->exit = sig_ctr(child_id, size_t_shell(mini_env->first_command));
	free(child_id);
}
