/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 18:44:36 by apesic            #+#    #+#             */
/*   Updated: 2025/05/17 18:44:39 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

bool	valid_export(t_shell *command)
{
	if (!command->command->next)
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
