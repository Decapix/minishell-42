/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:32:04 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/14 06:29:11 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	write_and_jump_quotes(char *buffer, char *str, int i)
{
	char	c;
	int		j;

	j = 0;
	while (!ft_isspace(str[i]) && str[i])
	{
		if (ft_isquote(str[i]))
		{
			c = str[i++];
			while (str[i] != c)
			{
				if (str[i] == '$' && c == '"')
				{
					buffer[j++] = -1;
					i++;
					continue ;
				}
				buffer[j++] = str[i++];
			}
			i++;
		}
		else
			buffer[j++] = str[i++];
	}
}

int	give_pipe(t_env *mini_env, t_shell **command, int i)
{
	t_io	*new_io;

	new_io = init_new_io(mini_env, *command, 0);
	if ((*command)->command)
	{
		new_io->io_mode = 3;
		(*command)->output++;
		*command = (*command)->next_command;
		new_io = init_new_io(mini_env, *command, 1);
		new_io->io_mode = 3;
	}
	return (i + 1);
}
