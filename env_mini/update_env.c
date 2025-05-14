/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:54:53 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/14 07:58:57 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_mini.h"

int	from_dollar_to_var(t_shell *command, char *var_value, int *i, int *j)
{
	char	*res;
	int		tmp;
	int		k;
	int		n;

	tmp = ft_strlen(var_value);
	res = ft_calloc(ft_strlen(command->command[*i]) + tmp + 1, sizeof(char));
	if (!res)
		return (1);
	k = -1;
	while (++k < *j)
		res[k] = command->command[*i][k];
	while (!ft_isspace(command->command[*i][*j]) && command->command[*i][*j])
		(*j)++;
	tmp = *j;
	n = 0;
	while (var_value[n])
		res[k++] = var_value[n++];
	while (command->command[*i][tmp])
		res[k++] = command->command[*i][tmp++];
	free(command->command[*i]);
	command->command[*i] = res;
	free(var_value);
	return (0);
}

char	*extract_dollar(t_env *mini_env, char *str)
{
	char	*buffer;
	t_env	*begin;
	int		len;

	len = ft_strlen(str);
	begin = mini_env;
	while (mini_env)
	{
		if (!ft_strncmp(mini_env->var_name, str, len))
			break ;
		mini_env = mini_env->next_var;
	}
	if (!mini_env)
		return (ft_strdup(""));
	buffer = ft_strdup(mini_env->var);
	free(str);
	if (!buffer)
		exit_program(begin, 2);
	return (buffer);
}

char	*dollar_found(t_shell **command, int i, int j)
{
	int		start;
	char	*buffer;

	if ((signed char)(*command)->command[i][j] != -1)
	{
		printf("problem with dollar find algo\n");
		exit(1);
	}
	start = ++j;
	while (!ft_isspace((*command)->command[i][j]) && (*command)->command[i][j])
		j++;
	buffer = copy_from_i_to_j(&start, j, (*command)->command[i]);
	if (!buffer)
		return (0);
	return (buffer);
}

char	*find_dollar(t_shell **command, int *i, int *j)
{
	signed char	c;

	while (*command)
	{
		if ((*command)->command)
		{
			*i = 0;
			while ((*command)->command[*i])
			{
				*j = 0;
				while ((signed char)(*command)->command[*i][*j])
				{
					c = (*command)->command[*i][*j];
					if (c == -1)
						return (dollar_found(command, *i, *j));
					(*j)++;
				}
				(*i)++;
			}
		}
		*command = (*command)->next_command;
	}
	return ("");
}

void	replace_dollar(t_env *mini_env, t_shell *command)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	j = 0;
	while (command)
	{
		buffer = find_dollar(&command, &i, &j);
		if (!buffer)
			exit_program(mini_env, 2);
		if (!buffer[0])
			return ;
		buffer = extract_dollar(mini_env, buffer);
		if (from_dollar_to_var(command, buffer, &i, &j))
			exit_program(mini_env, 2);
	}
}
