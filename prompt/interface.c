/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 12:22:14 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/13 17:44:09 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	change_g(void)
{
	g_status = 0;
}

void	sig_handler_execution(int signal)
{
	g_status = signal;
}

void	sig_handler_readline(int i)
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

char	*show_shell(void)
{
	char					*prompt;
	static struct sigaction	*act;

	change_g();
	if (!act)
	{
		act = ft_calloc(1, sizeof(struct sigaction));
		if (!act)
			return (0);
	}
	act->sa_handler = sig_handler_readline;
	sigaction(SIGINT, act, NULL);
	prompt = readline("minishell % ");
	if (prompt)
		check_out_prompt(&prompt);
	if (prompt)
		if (prompt[0])
			add_history(prompt);
	act->sa_handler = sig_handler_execution;
	sigaction(SIGINT, act, NULL);
	return (prompt);
}
