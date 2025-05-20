/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:08:17 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/20 12:40:44 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	change_sigint(int mode)
{
	static struct sigaction	*act;

	if (!mode)
	{
		if (act)
			free(act);
		return (1);
	}
	if (!act)
	{
		act = ft_calloc(1, sizeof(struct sigaction));
		if (!act)
			return (0);
	}
	if (mode == 1)
		act->sa_handler = &sigint_handler_readline;
	if (mode == 2)
		act->sa_handler = &sigint_handler_execution;
	sigaction(SIGINT, act, NULL);
	return (1);
}

int	change_signal(int mode)
{
	int	status;

	status = change_sigint(mode);
	if (!status)
		return (status);
	return (status);
}
