/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_exits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:39:58 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/21 14:26:18 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_char(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

int	print_error(int error_code)
{
	if (error_code == 1)
		ft_putstr_fd("error near parse: \\n\n", 2);
	if (error_code == 2)
		ft_putstr_fd("mem allocation as failed\n", 2);
	if (error_code == 3)
		ft_putstr_fd("unclosed quotes\n", 2);
	if (error_code == 5)
		ft_putstr_fd("pipe creation as failed\n", 2);
	if (error_code == 6)
		ft_putstr_fd("input file does not exist\n", 2);
	if (error_code == 7)
		ft_putstr_fd("parse error near: |\n", 2);
	if (error_code == 8)
		ft_putstr_fd("parse error near: <\n", 2);
	if (error_code == 9)
		ft_putstr_fd("parse error near: >\n", 2);
	if (error_code == 10)
		ft_putstr_fd("parse error near token\n", 2);
	return (-1);
}

void	free_io(t_io *to_free)
{
	t_io	*tmp;

	while (to_free)
	{
		tmp = to_free->next_io;
		if (to_free->io_name)
			free(to_free->io_name);
		free(to_free);
		to_free = tmp;
	}
}

void	free_command_struct(t_shell *command)
{
	t_shell	*tmp;
	t_list	*tmp2;

	while (command)
	{
		tmp = command->next_command;
		if (command->input)
			free_io(command->first_input);
		while (command->command)
		{
			tmp2 = command->command->next;
			if (command->command->str)
				free(command->command->str);
			free(command->command);
			command->command = tmp2;
		}
		if (command->output)
			free_io(command->first_output);
		free(command);
		command = 0;
		command = tmp;
	}
}

void	exit_program(t_env *mini_env, int error_code)
{
	t_env	*tmp;

	print_error(error_code);
	change_signal(0);
	if (mini_env->first_command && error_code != -1)
		free_command_struct(mini_env->first_command);
	while (mini_env)
	{
		tmp = mini_env->next_var;
		if (mini_env->var_name)
			free(mini_env->var_name);
		if (mini_env->var)
			free(mini_env->var);
		free(mini_env);
		mini_env = tmp;
	}
	rl_clear_history();
	exit(error_code);
}
