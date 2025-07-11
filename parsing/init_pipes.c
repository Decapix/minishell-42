/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:32:04 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/21 16:07:11 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	give_pipe(t_env *mini_env, t_shell **command, int i)
{
	t_io	*tmp;

	tmp = init_new_io(mini_env, *command, 0);
	tmp->io_mode = 3;
	(*command)->output++;
	*command = (*command)->next_command;
	(*command)->input++;
	(*command)->first_input = init_new_io(mini_env, *command, 1);
	(*command)->first_input->io_mode = 3;
	return (i + 1);
}
