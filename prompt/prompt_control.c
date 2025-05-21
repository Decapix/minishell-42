/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:26:05 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/21 18:28:23 by jlepany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

int	ask_for_pipe(char **str)
{
	char	*res;
	char	*tmp;

	tmp = readline("> ");
	res = ft_strjoin(*str, " ");
	free(*str);
	*str = ft_strjoin(res, tmp);
	free(tmp);
	free(res);
	return (prompt_compliance(*str));
}

int	prompt_compliance(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '|')
		return (print_error(7));
	while (ft_isprint(str[i]))
		i++;
	i--;
	while (ft_isspace(str[i]))
		i--;
	if (str[i] == '|')
		return (1);
	return (0);
}

int	unclosed_quotes(char *str)
{
	int		i;
	char	c;
	int		quotes;

	i = 0;
	c = 0;
	quotes = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) && !quotes)
		{
			quotes = 1;
			c = str[i];
		}
		else if (str[i] == c)
			quotes = 0;
		i++;
	}
	if (quotes)
	{
		free(str);
		ft_putstr_fd("parse error near: unclosed quotes\n", 2);
	}
	return (quotes);
}

int	alone_token(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		c = str[i++];
		if (ft_isquote(c))
			while (str[i] != c && !str[i])
				i++;
		if (c == '>' || c == '<')
		{
			if (str[i] == c)
				i++;
			while (ft_isspace(str[i]))
				i++;
			if (ft_istoken(str[i]))
				return (print_error(10));
			if (!str[i] || str[i] == '\n')
				return (print_error(1));
		}
	}
	return (0);
}

int	check_out_prompt(char **prompt)
{
	int	status;

	if (!(*prompt))
		return (0);
	if (!(*prompt)[0])
		return (1);
	if (unclosed_quotes(*prompt))
		return (1);
	if (alone_token(*prompt))
		return (1);
	status = prompt_compliance(*prompt);
	while (status == 1)
		status = ask_for_pipe(prompt);
	if (status == -1)
		return (1);
	return (0);
}
/*
int	main(void)
{
	char	*str;

	str = readline("test for prompt> ");
	if (!str)
		return (printf("no prompt given\n"));
	else
	{
		check_out_prompt(&str);
		printf("prompt is: %s\n", str);
		free(str);
	}
}*/
