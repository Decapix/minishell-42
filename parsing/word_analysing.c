/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_analysing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <jlepany@student.42,fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:39:02 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/15 14:53:37 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	else
		return (0);
}

int	ft_isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	ft_isquote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	else
		return (0);
}

int	ft_isprint(char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

int	check_the_char(t_env *env, t_shell **command, char *str, int i)
{
	char	c;
	int		tmp;

	c = str[i];
	if (c == '<')
		i = give_input(env, *command, str, i);
	else if (c == '>')
		i = give_output(env, *command, str, i);
	else if (c == '|')
	{
		i = give_pipe(env, command, i);
		tmp = i;
		while (ft_isspace(str[tmp]))
			tmp++;
		if (str[tmp] == '|')
			return (-1);
	}
	else if (ft_isprint(c))
		i = give_command_name(env, *command, str, i);
	return (i);
}
