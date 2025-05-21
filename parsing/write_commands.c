/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:04:39 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/21 17:32:29 by jlepany          ###   ########.fr       */
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

int	copy_correct_var(t_env *mini_env, char *str, char *buffer, int i)
{
	char	*tmp;

	if (i == -1)
		return (ft_strcopy(buffer, "$"));
	tmp = ft_strndup(&str[1], i - 1);
	if (!tmp)
		exit_program(mini_env, 2);
	while (mini_env)
	{
		if (!ft_strncmp(mini_env->var_name, tmp, i + 1))
		{
			free(tmp);
			tmp = 0;
			ft_strcopy(buffer, mini_env->var);
			break ;
		}
		mini_env = mini_env->next_var;
	}
	if (tmp)
		free(tmp);
	return (0);
}

int	change_dollar(t_env *mini_env, char *buffer, char *str, int quotes)
{
	int		i;

	i = 0;
	if (str[i++] != '$')
		ft_putstr_fd("something wrong with change dollar\n++", 2);
	if (str[i] == '?')
		return (ft_strcopy(buffer, mini_itoa(mini_env->exit)), i + 1);
	while (!ft_isspace(str[i]) && !ft_istoken(str[i]) && ft_isdollar(str[i]))
	{
		if (ft_isquote(str[i]) && !quotes && str[i] != '"')
			i += skip_till_quote(&str[i]);
		if (str[i] == '"' && quotes)
			break ;
		if (str[i] == '$')
			break ;
		i++;
	}
	if (!mini_env->var_name)
		return (i);
	if (ft_isspace(str[1]) || !str[1] || ((str[1] == '"' && quotes)))
		copy_correct_var(mini_env, str, buffer, -1);
	copy_correct_var(mini_env, str, buffer, i);
	return (i);
}

int	handle_quotes(t_env *mini_env, char *buffer, char *str, int *i)
{
	int		j;
	char	c;

	j = 0;
	c = str[(*i)++];
	while (str[(*i)] != c)
	{
		if (str[(*i)] == '$' && c == '"')
		{
			*i += change_dollar(mini_env, &buffer[j], &str[(*i)], 1);
			j = ft_strlen(buffer);
		}
		else
			buffer[j++] = str[(*i)++];
	}
	(*i)++;
	return (j);
}

int	write_and_jump_quotes(t_env *mini_env, char *buffer, char *str, int i)
{
	int		j;

	j = 0;
	while (!ft_isspace(str[i]) && !ft_istoken(str[i]) && str[i])
	{
		if (ft_isquote(str[i]))
			j += handle_quotes(mini_env, &buffer[j], str, &i);
		else
		{
			if (str[i] == '$')
			{
				i += change_dollar(mini_env, &buffer[j], &str[i], 0);
				j = ft_strlen(buffer);
			}
			else
				buffer[j++] = str[i++];
		}
	}
	return (i);
}
