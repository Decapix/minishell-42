/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:32:04 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/15 14:05:06 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
