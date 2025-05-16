/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:04:39 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/16 15:54:20 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	skip_till_quote(char *str)
{
	int		i;
	char	c;

	i = 0;
	if (!ft_isquote(str[i]))
		ft_putstr_fd("error with skip till quote in writecommand.c\n", 2);
	c = str[i++];
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	change_dollar(t_env *mini_env, char *buffer, char *str, int quotes)
{
	int		i;

	i = 0;
	if (str[i] != '$')
		ft_putstr_fd("something wrong with change dollar\n", 2);
	while (!ft_isspace(str[i]) && !ft_istoken(str[i]) && str[i])
	{
		if (ft_isquote(str[i]) && !quotes && str[i] != '"')
			i += skip_till_quote(&str[i]);
		if (str[i++] == '"' && quotes)
			break ;
	}
	if (!mini_env->var_name)
		return (i);
	while (mini_env)
	{
		if (!ft_strncmp(mini_env->var_name, buffer, i))
		{
			ft_strcopy(buffer, mini_env->var);
			break ;
		}
		mini_env = mini_env->next_var;
	}
	return (i);
}

int	write_and_jump_quotes(t_env *mini_env, char *buffer, char *str, int i)
{
	char	c;
	int		j;

	j = 0;
	while (!ft_isspace(str[i]) && !ft_istoken(str[i]) && str[i])
	{
		if (ft_isquote(str[i]))
		{
			c = str[i++];
			while (str[i] != c)
			{
				if (str[i] == '$' && c == '"')
					i += change_dollar(mini_env, &buffer[j], &str[i], 1);
				buffer[j++] = str[i++];
			}
			i++;
		}
		else
		{
			if (str[i] == '$')
				i += change_dollar(mini_env, &buffer[j], &str[i], 0);
			buffer[j++] = str[i++];
		}
	}
	return (i);
}
