/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:46:02 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/17 06:02:01 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**t_env_to_arr(t_env *mini_env)
{
	t_env	*tmp;
	char	**env_arr;
	char	*buffer;
	int		i;

	env_arr = ft_calloc(ft_envsize(mini_env) + 1, sizeof(char *));
	if (!env_arr)
		exit_program(mini_env, 2);
	i = 0;
	tmp = mini_env;
	while (mini_env && mini_env->var_name)
	{
		buffer = ft_strjoin(mini_env->var_name, "=");
		if (!buffer)
			exit_program(tmp, 2);
		env_arr[i] = ft_strjoin(buffer, mini_env->var);
		if (!env_arr[i++])
		{
			free_double_char(env_arr);
			exit_program(tmp, 2);
		}
		free(buffer);
		mini_env = mini_env->next_var;
	}
	return (env_arr);
}

void	execute_buildin(t_env *mini_env, char **envp, char **arg, t_shell *cmd)
{
	if (!ft_strncmp(cmd->command->str, "echo", 5))
		ft_echo(arg);
	if (!ft_strncmp(cmd->command->str, "exit", 5))
		ft_exit(mini_env, envp);
	if (!ft_strncmp(cmd->command->str, "env", 4))
		ft_env(mini_env);
	if (!ft_strncmp(cmd->command->str, "pwd", 4))
		ft_pwd();
	if (!ft_strncmp(cmd->command->str, "export", 7))
		if (cmd->command->next)
			ft_export(mini_env, cmd);
	if (!ft_strncmp(cmd->command->str, "unset", 6))
		ft_unset(mini_env, cmd);
	if (!ft_strncmp(cmd->command->str, "cd", 3))
		ft_cd(mini_env, cmd);
	free_double_char(envp);
	exit_program(mini_env, 0);
}

void	set_redirection(int fd[4], t_shell *command)
{
	char buffer[100];

	// Log what we're doing
	snprintf(buffer, sizeof(buffer),
		"CMD: %s, input=%d, output=%d, fds=[%d,%d,%d,%d]\n",
		command->command->str, command->input, command->output,
		fd[0], fd[1], fd[2], fd[3]);
	write(2, buffer, ft_strlen(buffer));

	// Handle input redirection
	if (command->input != 0)
	{
		write(2, "Redirecting stdin\n", 18);
		if (dup2(fd[2], STDIN_FILENO) == -1)
			perror("dup2 input error");
		close(fd[2]);
	}

	// Handle output redirection
	if (command->output != 0)
	{
		write(2, "Redirecting stdout\n", 19);
		if (dup2(fd[3], STDOUT_FILENO) == -1)
			perror("dup2 output error");
		close(fd[3]);
	}

	// Close all unused file descriptors
	int i;
	for (i = 0; i < 4; i++)
	{
		if (fd[i] > 2 &&
			!((i == 2 && command->input != 0) ||
			  (i == 3 && command->output != 0)))
		{
			close(fd[i]);
		}
	}
}

char	**t_lst_to_arr(t_env *mini_env, t_list *lst, char **envp)
{
	int		len;
	int		i;
	char	**res;

	len = ft_lstsize(lst);
	res = ft_calloc(len + 1, sizeof(char *));
	if (!res)
	{
		free_double_char(envp);
		exit_program(mini_env, 2);
	}
	i = 0;
	while (lst)
	{
		res[i] = ft_strdup(lst->str);
		if (!res)
		{
			free_double_char(envp);
			free_double_char(res);
			exit_program(mini_env, 2);
		}
		lst = lst->next;
		i++;
	}
	return (res);
}

int	exec_com(t_env *mini_env, t_shell *command, int fd[4])
{
	pid_t	id_command;
	char	**envp;
	char	**arg;
	char	buffer[100];

	// Log command execution
	snprintf(buffer, sizeof(buffer), "Executing command: %s\n",
		command->command->str);
	write(2, buffer, ft_strlen(buffer));

	id_command = fork();
	if (!id_command)
	{
		// In child process
		envp = t_env_to_arr(mini_env);
		arg = t_lst_to_arr(mini_env, command->command, envp);

		// Set up stdin/stdout redirections
		set_redirection(fd, command);

		// Execute the command
		if (command->is_buildin)
			execute_buildin(mini_env, envp, arg, command);
		execve(command->command->str, arg, envp);
		error_child(mini_env, command->command, arg, envp);
	}

	// In parent process
	// Close file descriptors that we passed to the child
	// so the parent doesn't hold them open

	if (fd[2] > 2)
	{
		write(2, "Parent closing fd[2] (stdin)\n", 29);
		close(fd[2]);
	}

	if (fd[3] > 2)
	{
		write(2, "Parent closing fd[3] (stdout)\n", 30);
		close(fd[3]);
	}

	// Handle exit builtin
	if (!command->next_command && !ft_strncmp(command->command->str, "exit", 5))
		return (1);

	return (id_command);
}
