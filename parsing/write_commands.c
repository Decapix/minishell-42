/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:04:39 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/15 16:59:24 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	change_dollar(t_env *mini_env, char *buffer, char *str, int i)
{
	int		j;

	j = i;
	if (buffer[i] != '$')
		ft_putstr_fd("something wrong with change dollar\n", 2);
	while (!ft_isspace(str[i]) && !ft_istoken(str[i]) && str[i])
		i++;
	if (!mini_env->var_name)
		return (i);
	while (mini_env)
	{
		if (!ft_strncmp(mini_env->var_name, buffer, i - j))
		{
			ft_strcopy(buffer, mini_env->var);
			break ;
		}
	}
	return (i);
}

void	write_and_jump_quotes(t_env *mini_env, char *buffer, char *str, int i)
	//write until space. until token too
{
	char	c;
	int		j;

	j = 0;
	while (!ft_isspace(str[i]) && ft_istoken(str[i]) && str[i])
	{
		if (ft_isquote(str[i]))
		{
			c = str[i++];
			while (str[i] != c)
			{
				if (str[i] == '$' && c == '"')
					i = change_dollar(mini_env, &buffer[j], str, i);
				buffer[j++] = str[i++];
			}
			i++;
		}
		else
		{
			buffer[j++] = str[i++];	
		}
	}
}
