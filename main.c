/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:11:19 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/21 17:15:44 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

char	*search_path(t_env *mini_env)
{
	while (mini_env)
	{
		if (mini_env->var)
			if (!ft_strncmp(mini_env->var_name, "PATH", 4))
				return (mini_env->var);
		mini_env = mini_env->next_var;
	}
	return (0);
}

char	*restart_shell(t_env *mini_env)
{
	char	*prompt;

	free_command_struct(mini_env->first_command);
	prompt = show_shell(mini_env);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	t_env			*mini_env;
	char			*prompt;
	char			**path;

	signal(SIGQUIT, SIG_IGN);
	if (argc != 1 || !argv[0])
		return (0);
	mini_env = set_up_env(envp);
	if (!mini_env)
		return (0);
	prompt = show_shell(mini_env);
	while (prompt)
	{
		while (init_prompt_structure(mini_env, prompt))
			prompt = restart_shell(mini_env);
		path = extract_path(search_path(mini_env));
		execute_command(mini_env, mini_env->first_command, path);
		prompt = restart_shell(mini_env);
	}
	exit_program(mini_env, -1);
	return (0);
}
