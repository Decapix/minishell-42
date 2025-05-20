/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:02:56 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/20 13:12:43 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_io	*init_new_io(t_env *mini_env, t_shell *command, int input)
{
	t_io	*new;
	t_io	*tmp;

	new = ft_calloc(1, sizeof(t_io));
	if (!new)
		exit_program(mini_env, 2);
	if (input)
	{
		tmp = command->first_input;
		if (!tmp)
			return (command->first_input = new);
	}
	else
	{
		tmp = command->first_output;
		if (!tmp)
			return (command->first_output = new);
	}
	while (tmp->next_io)
		tmp = tmp->next_io;
	tmp->next_io = new;
	return (new);
}

int	give_input(t_env *mini_env, t_shell *command, char *str, int i)
{
	t_io	*new_io;

	if ((!str[i + 1]) || (str[i + 1] == '<' && !str[i + 2]))
		return (print_error(8));
	new_io = init_new_io(mini_env, command, 1);
	if (str[++i] == '<')
	{
		new_io->io_mode = 2;
		i++;
	}
	else
		new_io->io_mode = 1;
	while (ft_isspace(str[i]))
		i++;
	if (ft_istoken(str[i]))
		return (print_error(8));
	i = give_name(mini_env, &new_io->io_name, str, i);
	command->input++;
	return (i);
}

int	give_output(t_env *mini_env, t_shell *command, char *str, int i)
{
	t_io	*new_io;

	if ((!str[i + 1]) || (str[i + 1] == '>' && !str[i + 2]))
		return (print_error(9));
	new_io = init_new_io(mini_env, command, 0);
	if (str[++i] == '>')
	{
		new_io->io_mode = 2;
		i++;
	}
	else
		new_io->io_mode = 1;
	while (ft_isspace(str[i]))
		i++;
	if (ft_istoken(str[i]))
		return (print_error(9));
	i = give_name(mini_env, &new_io->io_name, str, i);
	command->output++;
	return (i);
}
