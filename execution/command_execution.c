/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:46:02 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/13 18:14:38 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	**t_env_to_arr(t_env *mini_env)
{
	t_env	*tmp;
	char	**env_arr;
	char	*buffer;
	int		i;

	env_arr = ft_calloc(ft_lstsize(mini_env) + 1, sizeof(char *));
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

void	execute_buildin(t_env *mini_env, char **envp, t_shell *command)
{
	if (!ft_strncmp(command->command[0], "exit", 5))
		ft_exit(mini_env, envp);
	if (!ft_strncmp(command->command[0], "env", 4))
		ft_env(envp);
	if (!ft_strncmp(command->command[0], "pwd", 4))
		ft_pwd();
	if (!ft_strncmp(command->command[0], "export", 7))
	{
		if (command->command[1])
			ft_export(mini_env, command);
		else
			ft_env(envp);
	}
	if (!ft_strncmp(command->command[0], "unset", 6))
		ft_unset(mini_env, command);
	free_double_char(envp);
	exit_program(mini_env, 0);
}

void	set_redirection(int fd[4], t_shell *command)
{
	if (command->input == 3)
		close(fd[0]);
	if (command->input != 0)
	{
		dup2(fd[2], 0);
		close(fd[2]);
	}
	if (command->output)
	{
		if (dup2(fd[3], 1) == -1)
			perror("fucking hell:");
		close(fd[3]);
	}
	if (command->output != 0)
		close(fd[3]);
}

int	exec_com(t_env *mini_env, t_shell *command, int fd[4])
	//if mem error from malloc in envp init, only one child is killed
{
	pid_t	id_command;
	char	**envp;

	id_command = fork();
	if (!id_command)
	{
		envp = t_env_to_arr(mini_env);
		set_redirection(fd, command);
		if (command->is_buildin)
			execute_buildin(mini_env, envp, command);
		execve(command->command[0], command->command, envp);
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd(command->command[0], 2);
		ft_putstr_fd("\n", 2);
		free_double_char(envp);
		exit_program(mini_env, 127);
	}
	if (command->input)
		close(fd[2]);
	if (command->output)
		close(fd[3]);
	if (!command->next_command && !ft_strncmp(command->command[0], "exit", 5))
		return (1);
	return (id_command);
}
