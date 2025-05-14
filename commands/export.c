/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:17:17 by apesic            #+#    #+#             */
/*   Updated: 2025/05/13 17:30:56 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

static bool	valid_export(t_shell *command)
{
	if (command->command[2])
		return (false);
	return (true);
}

void	add_var_name(t_env *begin, t_env *mini_env, char *var, int *i)
{
	int		j;
	char	*res;

	while (var[*i] && var[*i] != '=')
		(*i)++;
	j = 0;
	res = ft_calloc(*i + 1, sizeof(char));
	if (!res)
		exit_program(begin, 2);
	while (j < *i)
	{
		res[j] = var[j];
		j++;
	}
	mini_env->var_name = res;
}

void	add_var_content(t_env *begin, t_env *mini_env, char *var, int i)
{
	char	*res;
	int		j;
	int		k;

	j = ++i;
	while (var[i])
		i++;
	res = ft_calloc(i - j + 1, sizeof(char));
	if (!res)
		exit_program(begin, 2);
	k = 0;
	while (j < i)
		res[k++] = var[j++];
	mini_env->var = res;
}

int	ft_export(t_env *mini_env, t_shell *command)
{
	int		i;
	t_env	*begin;

	i = 0;
	begin = mini_env;
	if (!valid_export(command))
		return (0);
	while (mini_env->next_var)
		mini_env = mini_env->next_var;
	mini_env->next_var = ft_calloc(1, sizeof(t_env));
	if (!mini_env->next_var)
		exit_program(begin, 2);
	mini_env = mini_env->next_var;
	add_var_name(begin, mini_env, command->command[1], &i);
	add_var_content(begin, mini_env, command->command[1], i);
	return (0);
}
