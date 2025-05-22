/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:00:58 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/22 00:00:00 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	count_args(t_list *arg_list)
{
	int		count;
	t_list	*current;

	count = 0;
	current = arg_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	handle_exit_errors(char *arg, t_env *mini_env, 
					t_list *arg_list, int *exit_code)
{
	if (!is_numeric(arg))
	{
		write(2, "minishell: exit: numeric argument required\n", 42);
		exit_program(mini_env, 255);
	}
	*exit_code = ft_atoi(arg);
	if (count_args(arg_list) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		*exit_code = 1;
	}
}

int	ft_exit(t_env *mini_env, t_leak *garbage, t_shell *cmd)
{
	int		exit_code;
	t_list	*arg_list;
	int		is_child;

	is_child = (getppid() != g_status);
	if (!is_child)
		write(1, "exit\n", 5);
	clean_garbage(garbage);
	exit_code = 0;
	arg_list = cmd->command;
	if (arg_list && arg_list->next)
		handle_exit_errors(arg_list->next->str, mini_env, arg_list, &exit_code);
	if (cmd->next_command == NULL)
		exit_program(mini_env, exit_code);
	return (exit_code);
}
