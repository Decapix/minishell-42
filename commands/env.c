/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:42:24 by apesic            #+#    #+#             */
/*   Updated: 2025/05/15 15:14:50 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	ft_env(t_env *mini_env, int export)
	// change to t_env and mode. if mode means it was called through export
	// then print all var event the one without char *var.
{
	while (mini_env)
	{
		if (mini_env->var_name)
		{
			if (!mini_env->var && !export)
			{
				mini_env = mini_env->next_var;
				continue ;
			}
			ft_putstr_fd(mini_env->var_name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(mini_env->var, 1);
			ft_putstr_fd("\n", 1);
		}
		mini_env = mini_env->next_var;
	}
	return (0);
}
