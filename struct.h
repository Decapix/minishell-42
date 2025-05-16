/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:16:50 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/15 12:18:10 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdio.h>
# include <stdbool.h>
# include <signal.h>

extern volatile sig_atomic_t	g_status;

typedef struct basic_list
{
	char				*str;
	struct basic_list	*next;
}	t_list;

typedef struct input_output
{
	int					io_mode;
	char				*io_name;
	struct input_output	*next_io;
}	t_io;

typedef struct shell_command
{
	int						input;
	t_io					*first_input;
	t_list					*command;
	int						output;
	t_io					*first_output;
	bool					is_buildin;
	struct shell_command	*next_command;
}							t_shell;

typedef struct var_environmment
{
	char					*var_name;
	char					*var;
	struct var_environmment	*next_var;
	t_shell					*first_command;
}			t_env;

#endif
