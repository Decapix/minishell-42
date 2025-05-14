/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlepany <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:26:05 by jlepany           #+#    #+#             */
/*   Updated: 2025/05/13 15:00:50 by jlepany          ###   ########.fr       */
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
	while (ft_isprint(str[i]))
		i++;
	i--;
	while (ft_isspace(str[i]))
		i--;
	if (str[i] == '|')
		return (1);
	return (0);
}

int	check_out_prompt(char **prompt)
{
	int	status;

	status = prompt_compliance(*prompt);
	while (status == 1)
		status = ask_for_pipe(prompt);
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
