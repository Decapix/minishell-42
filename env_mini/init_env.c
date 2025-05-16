/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:25:40 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/16 12:10:50 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_mini.h"

int	search_for_var(char **envp, char *var, int len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], var, len))
			return (i);
		i++;
	}
	return (-1);
}

void	give_simple_env(t_env *mini_env)
{
	mini_env->var_name = ft_strdup("PATH");
	if (!mini_env->var_name)
		return (free(mini_env));
	mini_env->var = ft_strdup("/usr/bin:/bin");
	if (!mini_env->var)
		return (free(mini_env->var_name), free(mini_env));
}

t_env	*set_up_env(char **envp)
{
	t_env	*mini_env;

	mini_env = ft_calloc(1, sizeof(t_env));
	if (!mini_env)
		exit_program(0, 2);
	if (!envp[0])
		give_simple_env(mini_env);
	else
		extract_env(mini_env, envp);
	if (!mini_env->var_name)
		exit_program(mini_env, 2);
	return (mini_env);
}
/*
int	main(int argc, char **argv, char **envp)
{
	t_env	*mini_env;

	if (argc > 2)
		return (0);
	if (!argv[0])
		return (0);
	mini_env = set_up_env(envp);
	while (mini_env)
	{
		printf("%s=%s\n", mini_env->var_name, mini_env->var);
		mini_env = mini_env->next_var;
	}
}*/
