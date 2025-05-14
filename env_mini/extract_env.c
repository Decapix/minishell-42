/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 22:27:00 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/09 13:47:43 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_mini.h"

char	*give_var_name(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	while (str[j] != '=' && str[j])
		j++;
	res = copy_from_i_to_j(&i, j, str);
	if (!res)
		return (0);
	return (res);
}

char	*give_var_value(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = ft_strlen(str);
	while (str[i] != '=' && str[i])
		i++;
	i++;
	res = copy_from_i_to_j(&i, j, str);
	if (!res)
		return (0);
	return (res);
}

void	extract_env(t_env *mini_env, char **envp)
{
	int		i;
	t_env	*begin;

	i = 0;
	begin = mini_env;
	while (envp[i])
	{
		mini_env->var_name = give_var_name(envp[i]);
		if (!mini_env->var_name)
			exit_program(begin, 2);
		mini_env->var = give_var_value(envp[i]);
		if (!mini_env->var)
			exit_program(begin, 2);
		if (envp[++i])
		{
			mini_env->next_var = ft_calloc(1, sizeof(t_env));
			if (!mini_env)
				exit_program(begin, 2);
			mini_env = mini_env->next_var;
		}
	}
}
