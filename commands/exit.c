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

int	ft_exit(t_env *mini_env, t_leak *garbage, t_shell *cmd)
{
	int		exit_code;
	t_list	*arg_list;
	char	*arg;

	write(1, "exit\n", 5);
	clean_garbage(garbage);
	exit_code = 0;
	arg_list = cmd->command;
	if (arg_list && arg_list->next)
	{
		arg = arg_list->next->str;
		if (!is_numeric(arg))
		{
			write(2, "minishell: exit: numeric argument required\n", 42);
			exit_program(mini_env, 255);
		}
		else
		{
			exit_code = ft_atoi(arg);
			if (count_args(arg_list) > 2)
			{
				write(2, "minishell: exit: too many arguments\n", 36);
				return (0);
			}
		}
	}
	if (cmd->next_command == NULL)
		exit_program(mini_env, exit_code);
	return (0);
}
