/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:00:58 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/21 16:15:46 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	ft_exit(t_env *mini_env, t_leak *garbage)
{
	clean_garbage(garbage);
	exit_program(mini_env, 0);
	return (1);
}
