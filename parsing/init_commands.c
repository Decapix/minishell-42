/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:36:08 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/16 15:40:06 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strndup(char *str, int n)
{
	char	*buffer;
	int		i;

	buffer = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!buffer)
		return (0);
	i = 0;
	while (str[i] && i < n)
	{
		buffer[i] = str[i];
		i++;
	}
	return (buffer);
}

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

int	ft_istoken(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	else
		return (0);
}

int	can_be_an_option(char c)
{
	if (ft_istoken(c) || c == '\n')
		return (0);
	if (c == ' ')
		return (0);
	else if (ft_isprint(c))
		return (1);
	else
		return (0);
}

int	give_command_name(t_env *mini_env, t_shell *command, char *str, int i)
{
	int		j;
	t_list	*tmp;
	t_list	*last;

	j = i;
	tmp = ft_calloc(1, sizeof(t_list));
	if (!tmp)
		exit_program(mini_env, 2);
	if (command->command)
	{
		last = command->command;
		while (last->next)
			last = last->next;
		last->next = tmp;
	}
	else
		command->command = tmp;
	i = give_name(mini_env, &tmp->str, str, j);
	return (i);
}
