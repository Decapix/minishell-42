/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:36:08 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/09 13:51:12 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_the_quote(char *str, int i)
{
	char	quote_type;

	quote_type = str[i++];
	while (str[i] != quote_type)
	{
		i++;
		if (str[i] == '\n')
			return (-1);
	}
	return (i);
}

int	can_be_an_option(char c)
{
	if (c == '>' || c == '|' || c == '\n')
		return (0);
	if (c == ' ')
		return (0);
	else if (ft_isprint(c))
		return (1);
	else
		return (0);
}

int	nb_arg(char *str, int i)
{
	int		options;

	options = 0;
	while (str[i] != '\n' && str[i] != '>' && str[i] != '|' && str[i])
	{
		if (ft_isspace(str[i]))
		{
			i++;
			continue ;
		}
		while (can_be_an_option(str[i]))
		{
			if (ft_isquote(str[i]))
				i = skip_the_quote(str, i);
			if (i == -1)
				return (-1);
			i++;
		}
		options++;
	}
	return (options);
}

int	give_command_name(t_env *mini_env, t_shell *command, char *str, int i)
{
	int	j;
	int	index;
	int	args;

	index = 0;
	j = i;
	args = nb_arg(str, j);
	if (args == -1)
		exit_program(mini_env, 3);
	command->command = ft_calloc(args + 1, sizeof(char *));
	if (!command->command)
		exit_program(mini_env, 2);
	i = give_name(mini_env, &command->command[index++], str, j);
	while (index < args)
	{
		if (i == '>')
			return (i);
		i = give_name(mini_env, &command->command[index++], str, i);
	}
	return (i);
}
