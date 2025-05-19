/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:17:17 by apesic            #+#    #+#             */
/*   Updated: 2025/05/16 14:13:48 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static int	extract_var_content(char *var, int i, t_env *mini_env)
{
	char	*content;
	int		j;
	int		k;
	t_env	*begin;

	begin = mini_env;
	j = ++i;
	while (var[i])
		i++;
	content = ft_calloc(i - j + 1, sizeof(char));
	if (!content)
		exit_program(begin, 2);
	k = 0;
	while (j < i)
		content[k++] = var[j++];
	free(mini_env->var);
	mini_env->var = content;
	return (1);
}

static int	find_and_update_var(t_env *mini_env, char *var, int max_len)
{
	while (mini_env)
	{
		if (mini_env->var_name && !ft_strncmp(mini_env->var_name, var, max_len)
			&& ft_strlen(mini_env->var_name) == max_len)
		{
			if (ft_strchr(var, '='))
				return (extract_var_content(var, max_len, mini_env));
			return (1);
		}
		mini_env = mini_env->next_var;
	}
	return (0);
}

static void	create_and_add_var(t_env *mini_env, char *var, int i)
{
	t_env	*begin;
	t_env	*last;

	begin = mini_env;
	last = mini_env;
	while (last->next_var)
		last = last->next_var;
	last->next_var = ft_calloc(1, sizeof(t_env));
	if (!last->next_var)
		exit_program(begin, 2);
	last = last->next_var;
	add_var_name(begin, last, var, &i);
	add_var_content(begin, last, var, i);
}

int	ft_export(t_env *mini_env, t_shell *command)
{
	int		i;
	char	*var;

	i = 0;
	if (!valid_export(command))
		return (0);
	var = command->command->next->str;
	while (var[i] && var[i] != '=')
		i++;
	if (find_and_update_var(mini_env, var, i))
		return (0);
	create_and_add_var(mini_env, var, 0);
	return (0);
}
