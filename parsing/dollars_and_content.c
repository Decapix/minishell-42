/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_and_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:22:49 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/19 12:24:52 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_strcopy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	return (0);
}

int	search_dollar_value(t_env *mini_env, char *name)
{
	if (name[0] == '?')
		return (ft_intlen(mini_env->exit));
	while (mini_env)
	{
		if (mini_env->var)
			if (!ft_strncmp(mini_env->var_name, name, ft_strlen(name) + 1))
				return (ft_strlen(mini_env->var));
		mini_env = mini_env->next_var;
	}
	return (0);
}

int	extract_dollar_name(t_env *mini_env, char *str, int *i, char c)
{
	int		j;
	char	*dollar_name;

	j = (*i)++;
	if (str[j] != '$')
		ft_putstr_fd("wtf pas de dollar???\n", 2);
	if (ft_isspace(str[j + 1]) || !str[j + 1])
		return (1);
	while (!ft_isspace(str[*i]) && ft_isdollar(str[*i]) == 1 && str[*i] != c)
	{
		if (str[*i] == '?' || str[*i] == '$')
			break ;
		(*i)++;
	}
	dollar_name = ft_strndup(&str[j + 1], ((*i) - j - 1));
	if (!dollar_name)
		exit_program(mini_env, 2);
	j = search_dollar_value(mini_env, dollar_name);
	free(dollar_name);
	return (j);
}

int	parsing_through_char(t_env *mini_env, char *str, int i)
{
	char	c;
	int		dollar_supp;

	dollar_supp = 0;
	while (!ft_isspace(str[i]) && str[i])
	{
		if (ft_isquote(str[i]))
		{
			c = str[i++];
			while (str[i] != c)
			{
				if (!str[i])
					return (i);
				if (str[i] == '$' && c == '"' && ft_isdollar(str[i]))
					dollar_supp += extract_dollar_name(mini_env, str, &i, c);
				else
					i++;
			}
		}
		if (str[i] == '$')
			dollar_supp += extract_dollar_name(mini_env, str, &i, 0);
		else
			i++;
	}
	return (i + dollar_supp);
}

int	give_name(t_env *mini_env, char **to_store, char *str, int i)
{
	int		str_size;
	char	*buffer;

	while (ft_isspace(str[i]))
		i++;
	str_size = parsing_through_char(mini_env, str, i) - i;
	buffer = ft_calloc(str_size + 1, sizeof(char));
	if (!buffer)
		exit_program(mini_env, 2);
	i = write_and_jump_quotes(mini_env, buffer, str, i);
	*to_store = buffer;
	return (i);
}
