/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:41:04 by apesic            #+#    #+#             */
/*   Updated: 2025/05/16 13:36:15 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	prune_element(t_env *mini_env)
{
	free(mini_env->var_name);
	mini_env->var_name = 0;
	free(mini_env->var);
	mini_env->var = 0;
	return (0);
}

int	search_list(t_env **begin, t_env *mini_env, char *str)
{
	t_env	*tmp1;
	t_env	*tmp2;

	tmp2 = 0;
	while (mini_env)
	{
		if (mini_env->var_name && !ft_strncmp(mini_env->var_name, str, ft_strlen(str) + 1))
		{
			tmp1 = mini_env->next_var;
			prune_element(mini_env);
			free(mini_env);
			if (!tmp2)
				*begin = tmp1;
			else
				tmp2->next_var = tmp1;
			return (0);
		}
		else
		{
			tmp2 = mini_env;
			mini_env = mini_env->next_var;
		}
	}
	return (1);
}

int	search_element(t_env *mini_env, char *str)
{
	if (mini_env->var_name && !ft_strncmp(mini_env->var_name, str, ft_strlen(str) + 1))
		return (prune_element(mini_env));
	else
		return (1);
}

int	ft_unset(t_env *mini_env, t_shell *command)
{
	t_list *cmd_args;
	t_env *begin;
	
	if (!mini_env || !command->command->next)
		return (0);
	
	begin = mini_env;
	cmd_args = command->command->next;
	
	while (cmd_args)
	{
		if (!mini_env->next_var)
			search_element(mini_env, cmd_args->str);
		else
			search_list(&begin, begin, cmd_args->str);
		cmd_args = cmd_args->next;
	}
	return (0);
}
