/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_str_to_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:29:47 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/20 12:38:37 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	how_many_commands(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (ft_isspace(str[i]))
		i++;
	if (!str[i])
		return (0);
	if (str[i] == '|')
		return (-1);
	while (str[i])
		if (str[i++] == '|')
			res++;
	return (res);
}

int	write_command(t_env *mini_env, t_shell *command, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		i = check_the_char(mini_env, &command, str, i);
		if (i == 1)
			print_error(7);
		if (i == -1)
			return (1);
	}
	return (0);
}

int	init_prompt_structure(t_env *mini_env, char *str)
{
	t_shell	*prompt;
	t_shell	*first_command;
	int		status;
	int		commands;

	commands = how_many_commands(str);
	if (commands == -1)
		exit_program(mini_env, 1);
	prompt = ft_calloc(1, sizeof(t_shell));
	if (!prompt)
		exit_program(mini_env, 2);
	first_command = prompt;
	mini_env->first_command = first_command;
	while (--commands > 0)
	{
		prompt->next_command = ft_calloc(1, sizeof(t_shell));
		if (!prompt->next_command)
			exit_program(mini_env, 2);
		prompt = prompt->next_command;
	}
	status = write_command(mini_env, first_command, str);
	free(str);
	return (status);
}
