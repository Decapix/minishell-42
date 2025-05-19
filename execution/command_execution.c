/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:46:02 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/19 17:40:34 by jlepany          ###   ########.fr       */
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
	if (command->input == 3)
		close(fd[0]);
	if (command->input != 0)
	{
		if (dup2(fd[2], 0) == -1)
			perror("gimme a break...");
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

	id_command = fork();
	if (!id_command)
	{
		envp = t_env_to_arr(mini_env);
		arg = t_lst_to_arr(mini_env, command->command, envp);
		set_redirection(fd, command);
		if (command->is_buildin)
			execute_buildin(mini_env, envp, arg, command);
		execve(command->command->str, arg, envp);
		error_child(mini_env, command->command, arg, envp);
	}
	if (command->input)
		close(fd[2]);
	if (command->output)
		close(fd[3]);
	if (!command->next_command && !ft_strncmp(command->command->str, "exit", 5))
		return (1);
	return (id_command);
}
