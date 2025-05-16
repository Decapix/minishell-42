/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:09:34 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/15 15:00:40 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"
# include "parsing/parsing.h"
# include "prompt/prompt.h"
# include "env_mini/env_mini.h"
# include "libft/libft.h"
# include "execution/execution.h"
# include <readline/readline.h>
# include <sys/ioctl.h>
# include <readline/history.h>
# include <stddef.h>

void	*ft_calloc(size_t nb, size_t size);
void	free_command_struct(t_shell *command);

int		print_error(int error_code);
void	exit_program(t_env *mini_env, int error_code);

#endif
