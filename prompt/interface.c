/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:22:14 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/20 12:40:15 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	change_g(void)
{
	g_status = 0;
}

void	sigint_handler_execution(int signal)
{
	g_status = signal;
}

void	sigint_handler_readline(int i)
{
	if (!i)
		printf("wrong signal received");
	rl_replace_line("", 0);
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

char	*show_shell(t_env *mini_env)
{
	char		*prompt;
	static int	status;

	change_g();
	prompt = 0;
	if (!status)
		status = change_signal(1);
	if (!status)
		exit_program(mini_env, 2);
	while (1)
	{
		prompt = readline("minishell % ");
		if (!check_out_prompt(&prompt))
			break ;
	}
	if (prompt)
		if (prompt[0])
			add_history(prompt);
	return (prompt);
}
