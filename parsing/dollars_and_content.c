/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_and_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:22:49 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/15 13:04:49 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strncopy(char *str, int n)
{
	char	*res;
	int		i;

	i = 0;
	res = ft_calloc(n + 1, sizeof(char));
	if (!res)
		return (0);
	while (i < n)
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

int	search_dollar_value(t_env *mini_env, char *name)
{
	while (mini_env->var_name)
	{
		if (mini_env->var)
			if (!ft_strncmp(mini_env->var, name, ft_strlen(name) + 1))
				return (ft_strlen(name));
		mini_env = mini_env->next_var;
	}
	return (0);
}

int	extract_dollar_name(t_env *mini_env, char *str, int *i)
{
	int		j;
	char	*dollar_name;

	j = *i;
	if (str[j] != '$')
		ft_putstr_fd("wtf pas de dollar???\n", 2);
	while (!ft_isspace(str[++j]))
		;
	if (!str)
		return (j - *i);
	dollar_name = ft_strncopy(&str[*i + 1], j);
	if (!dollar_name)
		exit_program(mini_env, 2);
	return (search_dollar_value(mini_env, dollar_name));
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
				if (str[i] == '$' && c == '"')
					dollar_supp = extract_dollar_name(mini_env, str, &i);
			}
		}
		if (str[i] == '$')
			dollar_supp = extract_dollar_name(mini_env, str, &i);
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
	str_size = parsing_through_char(mini_env, str, i);
	buffer = ft_calloc(str_size + 1, sizeof(char));
	if (!buffer)
		exit_program(mini_env, 2);
	write_and_jump_quotes(buffer, str, i);
	*to_store = buffer;
	return (i);
}
