/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 12:02:56 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/15 14:03:53 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parsing_through_char(t_env *mini_env, char *str, int i)
{
	char	c;

	while (!ft_isspace(str[i]) && str[i])
	{
		if (ft_isquote(str[i]))
		{
			c = str[i++];
			while (str[i] != c)
			{
				if (!str[i])
					exit_program(mini_env, 0);
				i++;
			}
		}
		i++;
	}
	return (i);
}

int	give_name(t_env *mini_env, char **to_store, char *str, int i)
{
	int		j;
	char	*buffer;

	if (str[i] == '<' || str[i] == '>')
		i++;
	while (ft_isspace(str[i]))
		i++;
	j = i;
	i = parsing_through_char(mini_env, str, i);
	if (j == i)
		exit_program(mini_env, 1);
	buffer = ft_calloc(i - j + 1, sizeof(char));
	if (!buffer)
		exit_program(mini_env, 2);
	write_and_jump_quotes(buffer, str, j);
	*to_store = buffer;
	return (i);
}

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

	if (!str[i + 1])
		exit_program(mini_env, 1);
	new_io = init_new_io(mini_env, command, 1);
	if (str[i + 1] == '<')
		new_io->io_mode = 2;
	else
		new_io->io_mode = 1;
	while (ft_isspace(str[i]))
		i++;
	if (ft_istoken(str[i]))
		return (print_error(8), -1);
	i = give_name(mini_env, &new_io->io_name, str, ++i);
	command->input++;
	return (i);
}

int	give_output(t_env *mini_env, t_shell *command, char *str, int i)
{
	t_io	*new_io;

	if (!str[i + 1])
		exit_program(mini_env, 2);
	new_io = init_new_io(mini_env, command, 0);
	if (str[i + 1] == '>')
		new_io->io_mode = 2;
	else
		new_io->io_mode = 1;
	while (ft_isspace(str[i]))
		i++;
	if (ft_istoken(str[i]))
		return (print_error(9), -1);
	i = give_name(mini_env, &new_io->io_name, str, i);
	command->output++;
	return (i);
}
