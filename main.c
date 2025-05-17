/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 00:11:19 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/17 06:47:22 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

char	*search_path(t_env *mini_env)
{
	t_env	*tmp;

	tmp = mini_env;
	while (mini_env)
	{
		if (!ft_strncmp(mini_env->var_name, "PATH", 4))
			return (mini_env->var);
		mini_env = mini_env->next_var;
	}
	printf("error! path not found\n");
	exit_program(tmp, -1);
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
		free_double_char(path);
		printf("exit status of command = %d\n", mini_env->exit);
		prompt = restart_shell(mini_env);
	}
	exit_program(mini_env, -1);
	return (0);
}
